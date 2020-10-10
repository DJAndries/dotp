# dotp

Small time-based one time authentication (TOTP) C library. OpenSSL based.

## Building

After ensuring the OpenSSL development library is installed, run `make`.

Library will be located in the `lib` folder.

## API

```
void dotp_b32_encode(char* dest, char* src, size_t src_size);

int dotp_b32_decode(char* dest, size_t* result_size, char* src);
```

These two functions encode/decode base32. This is useful for loading serialized TOTP secret keys. Resulting values will be found in `dest`. Non-zero return value from the decode function indicates failure.

```
int dotp_hotp_value(char* dest, char* key, size_t key_size,
  uint64_t counter, size_t ndigits);
```

Produces HOTP value with a given key, counter and digit length. Non-zero return value indicates failure.

```
int dotp_totp_value(char* dest, char* key, size_t key_size,
  size_t duration_len, size_t ndigits);
```

Produces TOTP value with given key, duration length (seconds) and digit length. Most common values for duration length and digit length are 30 and 6, respectively.