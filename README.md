# alarm-pompa

ESP01-1MB
Base on ESP8266

ESP01 1M yang diprogram dengan menggunakan PlatformIO dapat melihat waktu yang berjalan saat ini dengan membuka homepage page dari sistem yang telah disediakan dalam koding

Saklar disambungkan ke kabel radar dan akan memutus kontak radar apabila pompa belum mati dalam waktu yang sudah ditentukan.
Saklar ditempatkan di GPIO3 (redled) dengan konfigurasi normally closed, yang akan terbuka bersamaan dengan led merah menyala (HIGH)

IP ESP01 menggunakan IP Statis dengan alamat 192.168.0.190

Telegram library menggunakan CTBot 2.1.9 dengan Arduino Json 6.19.0 ( Wajib dibawah 6.2.0 karena error)

v1 - Menggunakan Webserver untuk pengecekan
v2 - Menggunakan telegram untuk pengontrolan