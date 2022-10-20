# alarm-pompa

ESP01-1M
Base on ESP8266

ESP01 1M yang diprogram dengan menggunakan PlatformIO sebelum menggunakan File Sisyem harus di di inisiasi pada file platform.ini
Kode ini menggunakna FS untuk menyimpan history waktu nyala sebelumnya, sebanyak 4 waktu akan disimpan dalam bentuk json

Inisiasi FS pada ESP01 menggunakan :
- board_build.ldscript
- board_build.filesystem

IP menggunakan IP Statis dengan alamat 192.168.0.190