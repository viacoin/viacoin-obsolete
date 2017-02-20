// Copyright (c) 2013 The Bitcoin Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

//
// Make the data file for the alert system unit tests
//

#include "alert.h"
#include "key.h"

#include "serialize.h"
#include "util.h"
#include "utilstrencodings.h"
#include "version.h"

#include <vector>
#include <fstream>
#include <string>

using namespace std;

#include <boost/filesystem/operations.hpp>
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

// create the alerts with high PROTOCOL VERSION and test it even higher.
// But leave it low(er) for all the included files above.  This way the
// test data is at a higher protocol version than the code and doesn't need
// be regenerated when the protocol version is bumped.
//
// thanks to Gavin @ commit feaec80
//
#ifdef PROTOCOL_VERSION
#undef PROTOCOL_VERSION
#endif
#define PROTOCOL_VERSION 890001

std::string strPrivKey;
int count = 0;

void SignAndSave(CAlert& alert, std::string filename)
{
    CKey key;
    extern int count;
    CDataStream sMsg(SER_NETWORK, PROTOCOL_VERSION);
    sMsg << (CUnsignedAlert)alert;
    alert.vchMsg = std::vector<unsigned char>(sMsg.begin(), sMsg.end());
    std::vector<unsigned char> vchPrivKey = ParseHex(strPrivKey);
    key.SetPrivKey(CPrivKey(vchPrivKey.begin(), vchPrivKey.end()), false); // if key is not correct openssl may crash
    if (!key.Sign(Hash(alert.vchMsg.begin(), alert.vchMsg.end()), alert.vchSig))
        throw runtime_error("Unable to sign the alert. Make sure the private key is valid and is supplied in hex form.");

    CDataStream signedAlertMsg(SER_NETWORK,PROTOCOL_VERSION);
    signedAlertMsg << alert;

    ofstream file(filename.c_str(), ofstream::binary | ofstream::app);
    ostream_iterator<unsigned char> fileout_iter(file);
    std::copy(signedAlertMsg.begin(),signedAlertMsg.end(), fileout_iter);
    file.close();

    ++count;
}


//
// alertTests contains 8 alerts, generated with this code:
//
int main (int argc, char *argv[])
{
    extern int count;

    if (argc != 2) {
        cout << "Usage: alert_tests_data <hex private key>" << endl << endl;
        return(1);
    }
    else
       strPrivKey = argv[1];

    // get the default file or another output file and truncate it
    std::string filename = "data/alertTests.raw";
    ofstream ofs(filename.c_str(), ios::trunc);
    ofs.close();

    try {
        CAlert alert;
        alert.nRelayUntil   = 60;
        alert.nExpiration   = 24 * 60 * 60;
        alert.nID           = 1;
        alert.nCancel       = 0;   // cancels previous messages up to this ID number
        alert.nMinVer       = 0;  // These versions are protocol versions
        alert.nMaxVer       = 999001;
        alert.nPriority     = 1;
        alert.strComment    = "Alert comment";
        alert.strStatusBar  = "Alert 1";

        SignAndSave(alert, filename);

        alert.setSubVer.insert(std::string("/Satoshi:0.1.0/"));
        alert.strStatusBar  = "Alert 1 for Satoshi 0.1.0";
        SignAndSave(alert, filename);

        alert.setSubVer.insert(std::string("/Satoshi:0.2.0/"));
        alert.strStatusBar  = "Alert 1 for Satoshi 0.1.0, 0.2.0";
        SignAndSave(alert, filename);

        alert.setSubVer.clear();
        ++alert.nID;
        alert.nCancel = 1;
        alert.nPriority = 100;
        alert.strStatusBar  = "Alert 2, cancels 1";
        SignAndSave(alert, filename);

        alert.nExpiration += 60;
        ++alert.nID;
        SignAndSave(alert, filename);

        ++alert.nID;
        alert.nMinVer = 11;
        alert.nMaxVer = 22;
        SignAndSave(alert, filename);

        ++alert.nID;
        alert.strStatusBar  = "Alert 2 for Satoshi 0.1.0";
        alert.setSubVer.insert(std::string("/Satoshi:0.1.0/"));
        SignAndSave(alert, filename);

        ++alert.nID;
        alert.nMinVer = 0;
        alert.nMaxVer = 999999;
        alert.strStatusBar  = "Evil Alert'; /bin/ls; echo '";
        alert.setSubVer.clear();
        SignAndSave(alert, filename);
    }
    catch (runtime_error e) {
        cerr << e.what() << endl;
        return (2);
    }

    cout << endl;
    cout << "Done!" << endl;
    cout << "Wrote " << count << " signed alerts to " << filename << endl;
    cout << "Now delete " << filename << ".h and re-run make to recreate it from the raw file." << endl << endl;
    cout << "Then remove test/test_test_bitcoin-alert_tests.o and run make one more time to cause it" << endl;
    cout << "to recompile the alert test with the newly created header file." << endl;
    cout << "The header and the raw datafile of signed alerts should be checked into source control." << endl;

    return (0);
}

