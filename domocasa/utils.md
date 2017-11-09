
# Certboot files casting
```
openssl x509 -outform der -in cert.pem -out server.crt
openssl pkey -in privkey.pem -out server.key
```