
FROM ubuntu:22.04

MAINTAINER Andrew Osterhout andrew.osterhout@utah.edu

ARG modelDir=../romp-models

ENV TZ=America/Denver
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt update && \
    apt -y upgrade && \
    apt -y install \
        build-essential \
        cmake \
        clang \
        git \
        ssh \
        bison \
        flex \
        libgmp-dev \
        python3 \
        python3-pip \
        wget \
        zsh \
        bat \
        rumur
RUN python3 -m pip install multiset

RUN useradd -ms $(which zsh) romp

# ========================================== Build Romp ========================================== #
RUN mkdir -p /home/romp/romp
ADD --chown=romp:romp --chmod=r-xr-xr-x . /home/romp/romp
# DBG: see if propper files got added
# RUN ls -lah /home/romp/romp && sleep 10
ENV MURPHI_VERSION="romp-v0.0.2"
RUN chmod +x /home/romp/romp/misc/xxd.py ; \
    chmod +x /home/romp/romp/libmurphi/src/make-version.py ; \
    mkdir -p /tmp/romp && \
    cd /tmp/romp && \
    cmake /home/romp/romp -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/clang++ -B/tmp/romp -G "Unix Makefiles" && \
    cd /tmp/romp/romp && \
    make && \
    make install && \
    cd /home/romp && \
    rm -rf /tmp/romp

# ========================================= Build Cmurphi ======================================== #
RUN mkdir -p /home/romp/Downloads ; mkdir -p /tmp/cmurphi && \
    wget http://mclab.di.uniroma1.it/site/softwareopensource/cmurphi5.5.0.tgz -O /tmp/cmurphi5.5.0.tgz && \
    tar -xzvf /tmp/cmurphi5.5.0.tgz -C /tmp && \
    rm -f /tmp/cmurphi5.5.0.tgz && \
    cd /tmp/cmurphi5.5.0/src && \
    make && \
    cp /tmp/cmurphi5.5.0/src/mu /usr/bin/mu && \
    rm -rf /tmp/cmurphi

# ============================================ Set Env =========================================== #
USER romp
WORKDIR /home/romp
CMD /bin/zsh --login

RUN mkdir -p /home/romp/models
COPY ./tests/*.m /home/romp/models
COPY ./tests/makefile /home/romp/models
COPY ./tests/README.md /home/romp/models

# Default powerline10k theme, no plugins installed
# RUN sh -c "$(wget -O- https://github.com/deluan/zsh-in-docker/releases/download/v1.1.5/zsh-in-docker.sh)"
RUN git clone --depth=1 https://github.com/romkatv/powerlevel10k.git ~/powerlevel10k && \
    echo "source ~/powerlevel10k/powerlevel10k.zsh-theme" >>~/.zshrc && \
    cd ~/powerlevel10k && \
    exec zsh

RUN echo "alias make='make ROMP=romp RUMUR=rumur CMURPHI=mu'" >> /home/romp/.bashrc
RUN echo "alias make='make ROMP=romp RUMUR=rumur CMURPHI=mu'" >> /home/romp/.zshrc

# DBG: make sure all model checkers are on path
# RUN eval echo eval "$(which romp)  --  $(which rumur)  --  $(which mu)  --  $(which make) " && sleep 10

