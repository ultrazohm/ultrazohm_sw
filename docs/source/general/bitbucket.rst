=========
Bitbucket
=========

Bitbucket is a cloud hosting service on which the remote repository of the UltraZohm is hosted <https://bitbucket.org>.
The repository is private at the moment, therefore one has to be registered at Bitbucket and request access to the repository at one of the admins.
Please use a descriptive username and work-related mail address.

Issues and pull requests are done with Bitbucket.

Issues
******
The Bitbucket **issue tracker** (<https://bitbucket.org/ultrazohm/ultrazohm_sw/issues>) is used to keep track of all issues with the UltraZohm.
**Issues** are bugs or problems with the system / the source code of the system and should be reported.

In the ``ultrazohm_sw`` repository you can click on issues to get to all open issues.
.. image:: ./images_bitbucket/issues.png

To report an issue click on ``Create issue``

.. image:: ./images_bitbucket/issue2.png

Enter a title for the issue which describes it. In the Description add more details and how to reproduce the problem.
You can name somebody to the issue who will be notified. Click ``Create issue`` to create the issue.

.. image:: ./images_bitbucket/issue4.png

Pull Request
************

After you finished a feature and you want to include your changes in the main repository you have to create a pull request in Bitbucket.
A pull request is an application to merge your changes from your feature branch to ``develop``.

.. image:: ./images_bitbucket/create_pull_request.png

In the *Create a pull request* plane you can choose which branches should be merged. Choose your feature branch on the left side and ``develop`` on the right.
Give the merge request a useful title and describe what the changes do. The commit messages are automatically added.
Next you assign reviewers with at least one maintainer and **click close feature after the pull request is merged**.
The reviewers will be notified and after the pull request is accepted, the feature branch will be deleted from the remote repository!

.. image:: ./images_bitbucket/pull_request2.png

The proposed changes can be discussed in the pull request and after the pull request ist approved one of the maintainer can merge the changes.

.. image:: ./images_bitbucket/pull_request4.png
