FROM centos:7

LABEL maintainer.name="Mischa Reitsma"
LABEL maintainer.email="reitsma.mischa@gmail.com"
LABEL version="1.1.0"

ADD gtminstall /tmp/

RUN yum install -y gcc g++ libicu-devel make openssl-devel wget which \
    && yum clean all

RUN groupadd gtm && useradd -g gtm gtm

RUN /tmp/gtminstall --group gtm --user gtm --installdir /opt/fis-gtm \
                    --noprompt-for-sys-cfg --prompt-for-group --utf8 default \
                    --verbose V6.3-010

USER gtm
RUN echo "source /opt/fis-gtm/gtmprofile" >> /home/gtm/.bashrc

ENTRYPOINT /bin/bash
