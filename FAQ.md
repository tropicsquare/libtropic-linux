# FAQ

This list might help you resolve some issues.

- [Cannot establish a secure session?](#cannot-establish-a-secure-session)

# Cannot establish a secure session?

You might have a TROPIC01 engineering sample. Some older engineering samples require a different SH0 key. Try compiling with `-DLT_SH0_PRIV_PATH=../libtropic/provisioning_data/sh0_priv_engineering_sample01.pem`. For example, use the following commands:
```bash
mkdir build && cd build && cmake -DLT_BUILD_EXAMPLES=1 -DLT_SH0_PRIV_PATH=../libtropic/provisioning_data/sh0_priv_engineering_sample01.pem .. && make
```
