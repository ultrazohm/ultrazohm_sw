# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.166.1/containers/ubuntu/.devcontainer/base.Dockerfile

# [Choice] Ubuntu version: bionic, focal
FROM docker.io/library/python:3

ARG USERNAME=uz_user
ARG USER_UID=1000
ARG USER_GID=1000

# Create the user
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    #
    # [Optional] Add sudo support. Omit if you don't need to install software after connecting.
    && apt-get update \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

# ********************************************************
# * Anything else you want to do like clean up goes here *
# ********************************************************

# [Optional] Set the default user. Omit if you want to keep the default as root.
USER $USERNAME

# [Optional] Uncomment this section to install additional OS packages.
RUN sudo apt-get update && export DEBIAN_FRONTEND=noninteractive \
     && sudo apt-get -y install --no-install-recommends build-essential \
                                                  gdb \
                                                  ruby \
                                                  texlive \
                                                  texlive-lang-german \
                                                  texlive-latex-extra \
                                                  texlive-pictures \
                                                  texlive-science \
                                                  ghostscript \
                                                  git-lfs \
                                                  doxygen
RUN sudo gem install ceedling
RUN sudo wget -O ~/vsls-reqs https://aka.ms/vsls-linux-prereq-script && sudo chmod +x ~/vsls-reqs && ~/vsls-reqs # Maybe required for liveshare https://docs.microsoft.com/en-us/visualstudio/liveshare/reference/linux#install-linux-prerequisites