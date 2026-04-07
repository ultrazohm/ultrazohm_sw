# Debian trixie-based Python image used for the devcontainer.
FROM docker.io/library/python:3.12-trixie

# [Optional] Uncomment this section to install additional OS packages.
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
     && apt-get -y install --no-install-recommends build-essential \
                                                  cmake \
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
                                                  openjdk-21-jdk \
                                                  ant

RUN gem install ceedling && ln -sf /usr/local/bin/ceedling /usr/bin/ceedling

RUN wget https://github.com/danmar/cppcheck/archive/refs/tags/2.20.0.tar.gz \
     && tar -xzf 2.20.0.tar.gz \
     && cmake -S cppcheck-2.20.0 -B cppcheck-2.20.0/build \
          -DCMAKE_BUILD_TYPE=Release \
          -DUSE_MATCHCOMPILER=On \
          -DHAVE_RULES=OFF \
          -DFILESDIR=/usr/share/cppcheck \
     && cmake --build cppcheck-2.20.0/build -j"$(nproc)" \
     && cmake --install cppcheck-2.20.0/build \
     && ln -sf /usr/local/bin/cppcheck /usr/bin/cppcheck \
     && rm -rf 2.20.0.tar.gz cppcheck-2.20.0

# Set env variables for gitpod, see https://github.com/gitpod-io/gitpod/issues/7110
ENV PYTHONUSERBASE=/workspace/.pip-modules
ENV PATH=$PYTHONUSERBASE/bin:$PATH
ENV PIP_USER=yes

ENV JAVA_HOME=/usr/lib/jvm/java-21-openjdk-amd64
ENV PATH="$JAVA_HOME/bin:$PATH"