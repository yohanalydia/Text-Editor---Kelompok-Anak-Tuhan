# Text-Editor_Kelompok-Anak-Tuhan

**PANDUAN TEXT EDITOR COTYPE--**

Disusun oleh:

Kelompok Anak Tuhan

Julian Sudiyanto - 103052300045 | Yohana Lydia - 103052330068

**Deskripsi Proyek**

COTYPE-- merupakan sebuah text editor yang dibangun berdasarkan console application. COTYPE-- bekerja dengan cara menerima input secara langsung dari keyboard pengguna kemudian memprosesnya berdasarkan fungsi-fungsi terkait. Dalam merancang text editor ini, penulis mengimplementasikan dua struktur data utama, yaitu Doubly Linked List dan Multi Linked List. Selain itu, penulis juga memanfaatkan  penggunaan struktur data Stack dalam pembuatan fitur Undo dan Redo.

**Fitur Utama**
1.	Input Huruf
Fitur ini memungkinkan pengguna untuk menginput karakter ke dalam text editor COTYPE--. Input dapat berupa karakter huruf, angka, dan simbol.

2.	Delete Huruf
Fitur Delete Huruf digunakan untuk menghapus karakter pada posisi sebelum posisi kursor. Fitur ini dapat digunakan dengan menekan tombol Backspace pada keyboard.

3.	Move Cursor to Left 
Fitur Move Cursor to Left akan memindahkan kursor sebanyak satu karakter ke kiri. Fitur ini dapat digunakan dengan menekan left arrow key pada keyboard. 

4.	Move Cursor to Right
Fitur Move Cursor to Right akan memindahkan kursor sebanyak satu karakter ke kanan. Fitur ini dapat digunakan dengan menekan right arrow key pada keyboard. 

5.	Move Cursor Up
Fitur Move Cursor Up akan memindahkan kursor sebanyak satu baris ke atas. Fitur ini dapat digunakan dengan menekan up arrow key pada keyboard. Kursor akan ditempatkan ke baris sebelumnya berdasarkan posisi kursor pada baris saat ini. 

6.	Move Cursor Down
Fitur Move Cursor Down akan memindahkan kursor sebanyak satu baris ke bawah. Fitur ini dapat digunakan dengan menekan down arrow key pada keyboard. Kursor akan ditempatkan ke baris setelahnya berdasarkan posisi kursor pada baris saat ini. 

7.	Select Huruf
Fitur Select Huruf akan mengubah warna latar belakang text/karakter yang dipilih. Ketika pengguna menekan kombinasi tombol ‘Ctrl + S’, pengguna akan diminta untuk memasukkan jumlah karakter yang ingin diseleksi/dipilih setelah posisi kursor. Fitur akan mengubah warna latar belakang karakter sebanyak jumlah karakter yang dimasukkan oleh pengguna. 

8.	Character To Uppercase
Fitur Character To Uppercase akan mengubah seluruh huruf yang telah diseleksi menjadi huruf kapital. Fitur ini dapat digunakan dengan menekan kombinasi tombol ‘Ctrl + U’.

9.	Character To Lowercase
Fitur Character To Uppercase akan mengubah seluruh huruf yang telah diseleksi menjadi huruf kecil. Fitur ini dapat digunakan dengan menekan kombinasi tombol ‘Ctrl + L’.

10.	Copy Huruf
Fitur Copy Huruf akan menyalin seluruh karakter yang sebelumnya sudah diseleksi dengan menggunakan fitur Select Huruf. Fitur ini dapat digunakan dengan menekan kombinasi tombol ‘Ctrl + C’.

11.	Cut Huruf
Fitur ini akan menyalin seluruh huruf yang sebelumnya telah diseleksi ke Clipboard, lalu menghapus huruf yang diseleksi tersebut. Fitur ini dapat digunakan dengan menekan kombinasi tombol ‘Ctrl + X’.

12.	Paste Huruf
Fitur Paste Huruf dapat menempelkan/menginput karakter yang sebelumnya sudah disalin dan berada dalam Clipboard, ke posisi kursor saat ini. Fitur ini dapat digunakan dengan menekan kombinasi tombol ‘Ctrl + P’.

13.	Search Word
Fitur Search Word berfungsi untuk mencari kata tertentu dalam keseluruhan teks. Ketika fitur ini digunakan, pengguna akan diminta untuk memasukkan kata yang ingin dicari. Selanjutnya, akan dilakukan penelusuran keseluruhan karakter dan mencari kata yang identik dengan kata yang dimasukkan. Jika ditemukan kata yang identik, kata tersebut akan diberi warna latar belakang kuning. Fitur ini dapat digunakan dengan menekan kombinasi tombol ‘Ctrl + E’.

14.	Replace Word
Fitur Replace Word dapat mengganti kata yang telah diseleksi sebelumnya dengan kata baru yang dimasukkan oleh pengguna. Ketika fitur ini digunakan, pengguna akan diminta untuk memasukkan kata baru yang akan digunakan sebagai pengganti. Setelah itu, fitur ini akan mengganti seluruh kata yang telah dipilih sebelumnya dengan kata baru tersebut. Fitur ini dapat digunakan dengan menekan kombinasi tombol ‘Ctrl + R’.

15.	Undo
Fitur Undo merupakan fitur yang dapat membatalkan perubahan yang dilakukan pengguna. Fitur ini dapat digunakan dengan menekan kombinasi tombol ‘Ctrl + Z’.

16.	Redo
Fitur Redo merupakan fitur yang dapat membatalkan pembatalan perubahan yang dilakukan sebelumnya dengan menggunakan fitur Undo. Fitur ini dapat digunakan dengan menekan kombinasi tombol ‘Ctrl + Y’.

17.	Show Instruction
Fitur Show Instruction merupakan fitur yang digunakan untuk menampilkan instruksi penggunaan text editor kepada pengguna. Fitur ini akan menampilkan shortcut yang dapat digunakan pengguna di dalam text editor COTYPE--. Fitur ini dapat digunakan dengan menekan kombinasi tombol ‘Ctrl + I’.

18.	Keterangan Text
Fitur ini akan menghitung jumlah huruf, jumlah kata, dan jumlah baris pada keseluruhan teks yang telah diinputkan. Fitur ini akan langsung ditampilkan tanpa perlu dipanggil.

19.	Display Kata 
Fitur Display Kata dapat menampilkan seluruh karakter yang telah ditambahkan ke dalam text editor. Tampilan disusun dari baris paling atas ke bawah, serta dari kiri ke kanan. Fitur ini akan langsung ditampilkan tanpa perlu dipanggil.

**Instruksi Instalasi dan Penggunaan**
1. Unduh seluruh kode program sebagai zip.
2. Ekstrak file yang telah diunduh.
3. Buka file COTYPE.cbp
4. Jalankan program.
