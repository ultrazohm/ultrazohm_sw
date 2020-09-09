=====================
Contribution Workflow
=====================

The git-workflow of the UltraZohm follows the git-flow model (<https://www.atlassian.com/git/tutorials/comparing-workflows/gitflow-workflow> <https://danielkummer.github.io/git-flow-cheatsheet/index.html>).
Why? Because it is an easy to follow set of rules for branching.
In addition to the git-flow model, pull requests are used for all merges to the ``main`` and ``develop`` branches (<https://www.atlassian.com/en/git/tutorials/making-a-pull-request>).
It is not permitted (and not possible) to merge to the ``main`` or ``develop`` branch without a pull request.

UltraZohm Workflow
------------------

The UltraZohm workflow is based on the git-flow workflow.
Git-flow is a popular branching model and supported by the git extension <https://github.com/nvie/gitflow/wiki/Command-Line-Arguments> as well as the GUI clients Sourcetree and GitKraken.

However, the git-flow tools are not needed, the important part is the set of rules for when to create which branch and how to merge it.
Relevant resources for git-flow can be found here:

  * <https://nvie.com/posts/a-successful-git-branching-model/>
  * <https://danielkummer.github.io/git-flow-cheatsheet/index.html>
  * <https://m.infos.seibert-media.net/Productivity/Git-Workflows+-+Der+Gitflow-Workflow.html> (German)
  * <https://www.atlassian.com/git/tutorials/comparing-workflows/gitflow-workflow>

.. image:: https://m.infos.seibert-media.net/resources/images/a5ec2c8628f19e0e6de758825b2cd25a-1:1541409413000-Gitflow-Workflow-4.png

The figure above shows the complete UultraZohm workflow.
The repository consists of the following branches:

1. ``main``: permanent existing branch with the stable version of the software. Each commit has a ``tag`` (see version numbers)
2. ``develop``: permanent existing branch with the current version of the software. Feature branches start from ``develop`` and are merged to develop (by pull requests). release branches start from develop
3. ``hotfix``: if a bug is found in the code it is fixed in a hotfix branch. Hotfix branches start from ``main`` and are merged to ``main`` and ``develop`` (by a pull request!). The revision number is incremented and and a new **tag** is created for ``main``. After the merge the branch is deleted.
4. ``release``: for a new release (minor or major) a release branch is created by the admins in which testing is done. ``release`` is merged to ``main`` and ``develop`` by a pull request and the revision number is created and a new **tag** is created for ``main``. After the merge, the branch is deleted.
5. ``feature``: new functionalities are developed in ``feature`` branches and merged to ``develop`` by a pull request. After the merge, the branch is deleted.

Hotfix branches should be linked to a Bitbucket issue <https://bitbucket.org/ultrazohm/ultrazohm_sw_v19_2/issues?status=new&status=open>.

.. note::
  For normal use of the system: only feature branches are relevant!
  Do not worry about the git-flow too much and ask in the forum if there are questions.

.. note::
  If you find a bug, create an issue!

.. warning::

  It is not possible and not allowed to merge anything to ``main`` or to push directly to ``main``!

Branch names
************

The naming convention for the branches is as following:

 * ``hotfix/branchname``  is a hotfix branch and ``branchname`` refers to the bug - e.g. ``hotfix/pwmtriger`` if there is a bug with the PWM trigger
 * ``release/branchname`` is a release branch with ``branchname`` referring to what the release is about - e.g. ``release/adc_ip_core`` if there is an update to the adc ip core
 * ``feature/featurename`` is a feature branch with ``featurename`` referring to what feature is developed - e.g. ``feature/oversampling`` if the feature is about oversampling

.. note::

  Please do not use your sandbox branch for the development of features!

Version number
**************

<<<<<<< HEAD
The version number is the **tag** of the commits of the ``main`` branch.
Depending on how much the code changed, it is either a revision (only bug fixes were made and no new features are added), a new sub-version (at least one new feature is added) or a new major version (multiple new features, big changes).
=======
The version numbers is the **tag** of the commits of the ``main`` branch.
Depending on how much the code changed it is either a revision (only bug fixes were made and no new features are added), a new sub-version (at least one new feature is added) or a new major version (multiple new features, big changes).
>>>>>>> update_docs_2020

::

  3.1.7
  │ │ │
  │ │ └───────── Revision: bug fixes, no new features (merged a hotfix)
  │ └─────────── Minor release, at least one new feature
  └───────────── Major release
