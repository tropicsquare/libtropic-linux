# FAQ

This list might help you to resolve some issues.

- [Cannot establish a secure session?](#cannot-establish-a-secure-session)

# Cannot establish a secure session?

Maybe you have TROPIC01 engineering sample - some of older engineering samples require different SH0 key. Try to compile with `-DLT_SH0_PRIV_PATH=../libtropic/provisioning_data/sh0_priv_engineering_sample01.pem`, for example like this:
```bash
mkdir build &&  cd build && cmake -DLT_BUILD_EXAMPLES=1 -DLT_SH0_PRIV_PATH=../libtropic/provisioning_data/sh0_priv_engineering_sample01.pem .. && make
```
