# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.166.1/containers/ubuntu/.devcontainer/base.Dockerfile

# [Choice] Ubuntu version: bionic, focal
FROM docker.io/library/python:3

# [Optional] Uncomment this section to install additional OS packages.
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
     && apt-get -y install --no-install-recommends build-essential \
                                                  gdb \
                                                  ruby \
                                                  texlive \
                                                  texlive-lang-german \
                                                  texlive-latex-extra \
                                                  texlive-pictures \
                                                  texlive-science \
                                                  pdf2svg \
                                                  ghostscript \
                                                  git-lfs \
                                                  doxygen
RUN gem install ceedling
RUN wget -O ~/vsls-reqs https://aka.ms/vsls-linux-prereq-script && chmod +x ~/vsls-reqs && ~/vsls-reqs # Maybe required for liveshare https://docs.microsoft.com/en-us/visualstudio/liveshare/reference/linux#install-linux-prerequisites
RUN wget https://github.com/danmar/cppcheck/archive/refs/tags/2.4.1.tar.gz && tar -xvf 2.4.1.tar.gz && cd cppcheck-2.4.1 && make SRCDIR=build CFGDIR=/usr/bin/cfg HAVE_RULES=yes install FILESDIR=/etc/cppcheck

