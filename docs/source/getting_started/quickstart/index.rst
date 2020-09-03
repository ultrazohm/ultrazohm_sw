==========
Quickstart
==========

Requirement: Toolchain is completely installed.
Git clone the following repositorys with your username ``BitbucketUsername``:

::

	git clone https://BitbucketUsername@bitbucket.org/ultrazohm/aa_ip_repository.git
	git clone https://BitbucketUsername@bitbucket.org/ultrazohm/cpld_lattice.git
	git clone https://BitbucketUsername@bitbucket.org/ultrazohm/javascope_standalone.git
	git clone https://BitbucketUsername@bitbucket.org/ultrazohm/ultrazohm_sw_v19_2.git


There should exist a directory in the following structure. Please note that a lot of relative paths of the project are case sensitive (e.g. AA_IP_Repository has to use capital letters).

::

  ./ultrazohm/
		AA_IP_Repository
		cpld_lattice
		javascope_standalone
		ultrazohm_sw_v19_2

..	toctree::
	:maxdepth: 2
	:caption: Quickstart

	vivado_firststeps
	vitis_import_projectTCL
	cpld_programming
