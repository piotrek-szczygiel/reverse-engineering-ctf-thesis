FROM ubuntu:20.04

RUN dpkg --add-architecture i386 \
    && apt-get update \
    && apt-get install -y libc6:i386 libncurses5:i386 libstdc++6:i386 openssh-server binutils python2 \
    && useradd -m admin \
    && useradd -s /bin/bash ctf \
    && echo "ctf:agh-reverse-engineering" | chpasswd \
    && mkdir -p /var/run/sshd

COPY greeter /home/admin/greeter
COPY decrypted_flag.txt /home/admin/flag.txt

RUN chown admin:admin /home/admin/greeter /home/admin/flag.txt \
    && chmod 4755 /home/admin/greeter \
    && chmod 600 /home/admin/flag.txt

EXPOSE 22
CMD ["/usr/sbin/sshd", "-D"]