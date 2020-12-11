FROM ubuntu:20.04

RUN dpkg --add-architecture i386 \
    && apt-get update \
    && apt-get install -y libc6:i386 libncurses5:i386 libstdc++6:i386 openssh-server binutils python2 \
    && useradd -m admin \
    && useradd -ms /bin/bash ctf \
    && echo "ctf:agh-reverse-engineering" | chpasswd \
    && mkdir -p /var/run/sshd

COPY secret-shell /home/admin/secret-shell
COPY decrypted_flag.txt /home/admin/access_code.txt

RUN chown admin:admin /home/admin/secret-shell /home/admin/access_code.txt \
    && chmod 4555 /home/admin/secret-shell \
    && chmod 400 /home/admin/access_code.txt

EXPOSE 22
CMD ["/usr/sbin/sshd", "-D"]