.. _ProjectStructure:

==================================
Structure of the UltraZohm Project
==================================

Communication channels
----------------------

.. mermaid::

  graph TD
  A[I have a problem with the UltraZohm]
  A --> B{What Problem <br> do I have?}
  B -->|A bug in the code| D[Issue on <br> Bitbucket]
  B -->|A tool does not work <br> e.g. Sourcetree, Vivado| E[Forum]
  B -->|Informal communication| F[Nextcloud Talk]

Project structure and user groups
---------------------------------

The overall structure of the UltraZohm will be described in the following sections.
Most of the information is based on <https://opensource.guide/> (and <https://opensource.guide/leadership-and-governance/> ).

User groups and name conventions
--------------------------------

The following user groups in the UltraZohm Community exist.
The user groups also determine the permissions for read/write of the different repositorys.
There are user groups in Bitbucket, in the UltraZohm-Cloud (Nextcloud) and the UltraZohm Forum, the naming conventions apply to all of them.
There are two category's of resources in the UltraZohm community:

* | Open source
  | All open source code and hardware of the UltraZohm system
* | Internal
  | The internal files, code and hardware of the UltraZohm system which is mostly organization, contracts and bills as well as personal control algorithms before publication of papers.
  | Furthermore files and code which can not be open sourced due to not owning the copyright (e.g. bought training material) is in this group.

The basic user groups are:

* | Admin
  | Can add and remove user, can grant and revoke permissions of other user groups (=mange teams)
  | This group is relevant for administration and organization of the community and has read/write to all repositorys as well as all folders in the cloud (e.g. billing information ).
* | Maintainer
  | The *core* group of people who organize the system, the community and maintain the code as well as the hardware components.
* | Contributor
  | All user who contribute code or hardware back to the UltraZohm community are a **contributor** and *everybody can be a contributor*!
  | However, it is recommended to get in touch with a maintainer if you want to contribute for the first time.
  | Contributor have write access to specific or all open source repositories / hardware folder.
* | User
  | Everybody who uses the system is a **user**, especially everybody who has a physical UltraZohm System which they can use.
  | All user have read access to all open source repositories and open source hardware and folder in the UltraZohm cloud.



+------------------+--------+------------+-------------+------+
|                  | Admin  | Maintainer | Contributor | User |
+==================+========+============+=============+======+
| Bitbucket        | 1      | 2          | 3           | 4    |
+------------------+--------+------------+-------------+------+
| Bitbucket        | 1      | 2          | 3           | 4    |
+------------------+--------+------------+-------------+------+
| Bitbucket        | 1      | 2          | 3           | 4    |
+------------------+--------+------------+-------------+------+

How to contribute
-----------------

TODO
