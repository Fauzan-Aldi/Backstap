# Backstap BOF
Ini adalah implementasi Beacon Object File dari Backstab Yaxser untuk digunakan dengan Cobalt Strike. 
![image](https://user-images.githubusercontent.com/91164728/157537763-684a4b2c-b677-40ea-af22-33e7fe5bb81d.png)

Pekerjaan tambahan akan mengubah pernyataan BeaconPrint untuk menggunakan sesuatu yang lebih rapi seperti metode Trustedsec.

# Perubahan
Beberapa perubahan dilakukan pada kode selama porting dari versi aslinya:

  1. Driver ProcExp tidak lagi disimpan/dimuat sebagai sumber daya, melainkan sebuah larik byte yang dikodekan dalam resource.c

  2. Ada beberapa kebocoran memori pada kode asli yang saya temukan dan selesaikan

# Untuk mengkompilasi:
Setelah awalnya mencoba mem-porting alat ini di Visual Studio, saya akhirnya mem-portingnya di Linux menggunakan mingw-gcc.  Saya belum mencoba mengkompilasi untuk x86, atau menggunakan VS (di mana akan ada masalah karena masalah C khusus gcc / VS).

Untuk mengkompilasi menggunakan gcc:
````
x86_64-w64-mingw32-gcc -o backstab.x64.o -Os -c main.c -DBOF -D_UNICODE
````

<ins>Pastikan Anda telah memperbarui mingw Anda ke versi terbaru! Saya mengalami masalah di mana versi saya memiliki file header yang kedaluwarsa, namun file header versi terbaru sudah benar.</ins>
