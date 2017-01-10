Viacoin Core version 0.10.10 is now available from:

  https://github.com/viacoin/viacoin/releases

This is a new minor version release, bringing bug fixes, the re-implementation
of FindAndDelete(). It is recommended to upgrade to this version as soon as possible.

Please report bugs using the issue tracker at github:

  https://github.com/viacoin/viacoin/issues

Upgrading and downgrading
=========================

How to Upgrade
--------------

If you are running an older version, shut it down. Wait until it has completely
shut down (which might take a few minutes for older versions), then run the
installer (on Windows) or just copy over /Applications/Viacoin-Qt (on Mac) or
viacoind/viacoin-qt (on Linux).

Notable changes since 0.10.10
============================


Transaction that takes 5 hours to verify
----------------------------------------------------------------

Re-implemented FindAndDelete() to build a new script by copying the parts 
that are not removed, instead of removing in-place. I don’t know if any 
other re-implementation of the consensus code is more vulnerable to this 
type of resource consumption

For more information, see: <https://github.com/bitcoin/bitcoin/pull/7907>

0.10.10 Change log
=================

Detailed release notes follow. This overview includes changes that affect
behavior, not code moves, refactors and string updates. For convenience in locating
the code changes and accompanying discussion, both the pull request and
git merge commit are mentioned.

- `390449b` Optimize and Cleanup CScript::FindAndDelete
- `126df74` Improve worst-case behavior of CScript::FindAndDelete
- `a369575` Replace memcmp with std::equal in CScript::FindAndDelete
- `d08654c` Fix replaypriority calculation error
- #6953 `8b3311f` alias -h for --help
- #6953 `97546fc` Change URLs to https in debian/control
- #6953 `38671bf` Update debian/changelog and slight tweak to debian/control
- #6953 `256321e` Correct spelling mistakes in doc folder
- #6953 `eae0350` Clarification of unit test build instructions
- #6953 `90897ab` Update bluematt-key, the old one is long-since revoked
- #6953 `a2f2fb6` build: disable -Wself-assign
- #6953 `cf67d8b` Bugfix: Allow mining on top of old tip blocks for testnet (fixes testnet-in-a-box use case)
- #6953 `b3964e3` Drop "with minimal dependencies" from description
- #6953 `43c2789` Split bitcoin-tx into its own package
- #6953 `dfe0d4d` Include bitcoin-tx binary on Debian/Ubuntu
- #6953 `612efe8` [Qt] Raise debug window when requested
- #6953 `3ad96bd` Fix locking in GetTransaction
- #6953 `9c81005` Fix spelling of Qt
- #6946 `94b67e5` Update LevelDB
- #6867 `5297194` Set TCP_NODELAY on P2P sockets
- #6836 `fb818b6` Bring historical release notes up to date
- #6852 `0b3fd07` build: make sure OpenSSL heeds noexecstack

Credits
=======

Thanks to everyone who directly contributed to this release:

- Alex Morcos
- ฿tcDrak
- Daniel Cousens
- Diego Viola
- Eric Lombrozo
- Esteban Ordano
- Gregory Maxwell
- Luke Dashjr
- MarcoFalke
- Matt Corallo
- Micha
- Mitchell Cash
- Peter Todd
- Pieter Wuille
- Wladimir J. van der Laan
- Zak Wilcox
- Patrick Strateman

And all those who contributed additional code review and/or security research:

- timothy on IRC for reporting the issue
- Vulnerability in miniupnp discovered by Aleksandar Nikolic of Cisco Talos
