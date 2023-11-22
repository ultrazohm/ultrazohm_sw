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
                                                  libpcre3-dev \
                                                  cppcheck

RUN gem install ceedling

# Set env variables for gitpod, see https://github.com/gitpod-io/gitpod/issues/7110
ENV PYTHONUSERBASE=/workspace/.pip-modules
ENV PATH=$PYTHONUSERBASE/bin:$PATH
ENV PIP_USER=yes