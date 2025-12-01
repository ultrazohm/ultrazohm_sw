# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.166.1/containers/ubuntu/.devcontainer/base.Dockerfile

# [Choice] Ubuntu version: bionic, focal
FROM docker.io/library/python:3.9.18-bullseye

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
                                                  texlive-luatex \
                                                  texlive-plain-generic \
                                                  pdf2svg \
                                                  ghostscript \
                                                  git-lfs \
                                                  doxygen \
                                                  libpcre3 \
                                                  libpcre3-dev

RUN gem install ceedling
RUN wget https://github.com/danmar/cppcheck/archive/refs/tags/2.12.1.tar.gz && tar -xvf 2.12.1.tar.gz && cd cppcheck-2.12.1 && make MATCHCOMPILER=yes FILESDIR=/usr/share/cppcheck HAVE_RULES=yes CXXFLAGS="-O2 -DNDEBUG -Wall -Wno-sign-compare -Wno-unused-function"

# Set env variables for gitpod, see https://github.com/gitpod-io/gitpod/issues/7110
ENV PYTHONUSERBASE=/workspace/.pip-modules
ENV PATH=$PYTHONUSERBASE/bin:$PATH
ENV PIP_USER=yes