# SoalShift_modul2_A12
Kelompok SISOP A12

Laporan Praktikum Sistem Operasi

1.	Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
Catatan : Tidak boleh menggunakan crontab.

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>

int main() {
  pid_t pid, sid;
  pid = fork();
  if (pid < 0) {
    exit(EXIT_FAILURE); }
  if (pid > 0) {
    exit(EXIT_SUCCESS); }
  umask(0);
  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE); }
  if ((chdir(".")) < 0) {
    exit(EXIT_FAILURE); }
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  // Tugas daemon adalah untuk menjalankan program
  // dan bekerjanya proses daemon terus-menerus sampai sleep(3) detik 

while(1){
        struct dirent *filex; 
        // Butuh type sama file jadi menggunakan dirent
        DIR *dir = opendir("/home/insane/");
        // opendir() adalah untuk membuka direktori.
        char* ptrsub;
        // variable untuk menyaring file .png
        char f1[100];
        // untuk menyimpan file .png
        char f2[100];
        // untuk menyimpan file _grey.png
        char loc[100];
        // menyimpan lokasi directory "/home/insane/modul2/gambar/"
                if (dir != NULL){
                        while((filex = readdir(dir)) != NULL) {
                          //readdir() akan membaca file dalam direktori satu per satu secara urut.
                          // Mengecek directory kosong atau tidak, jika tidak kosong maka bagian bawah berjalan
                                strcpy(f1, filex->d_name); 
                                // strcpy untuk  menyalin  string  asal  ke-variabel  string  tujuan
                                // Mengambil semua nama file dalam directory tersebut di masukkin dalam f1
                                ptrsub = strstr(f1, ".png");
                                // strstr untuk mencari lokasi substring dari suatu string
                                // Untuk menyaring file .png
                if(ptrsub != NULL){
                // Jadi jika ptrsub tidak sama dengan NULL maka melakukan bagian di bawah
                        strncpy(f2, filex->d_name, strlen(filex->d_name) - 4);
                        // strlen digunakan untuk menghitung panjang karakter pada suatu string.
                        // strncpy untuk melakukan penyalinan string sebanyak n karakter dari variabel 2 ke variabel 1
                        // Mengambil semua file .png namun tidak dengan tipe file yaitu isi dari f2
                        strcat(f2, "_grey.png");
                        // strcat digunakan untuk menggabungkan dua string menjadi satu.
                        // semua nama file yang ada di f2 itu akan berubah menjadi _grey.png
                        strcpy(loc,"/home/insane/modul2/gambar/");
                        // isi dari loc adalah /home/insane/modul2/gambar/
                        strcat(loc, f2);
                        // jadi directory tadi digabung dengan _grey.png 
                        rename(f1 , loc);
                        // terakhir rename untuk mengubah .png atau f1 menjadi _grey.png
                                }
                                                                }
                                }
        sleep(30);
        }
        exit(EXIT_SUCCESS);
}


2.	Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.
Catatan: Tidak boleh menggunakan crontab

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <pwd.h> 
#include <grp.h> 

int main() {
  pid_t pid, sid;
  pid = fork();
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }
  umask(0);
  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }
  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  // Tugas daemon adalah untuk menjalankan program
  // dan bekerjanya proses daemon terus-menerus sampai sleep(3) detik 
  
  while(1) 
  {
   char dir[] = "/home/insane/hatiku/elen.ku"; 
//Mengambil directory jadi dir ini menyimpan string "lokasi file ellenku" 
   struct stat info;
//Untuk deklarasi struct, untuk mengambil permission, group id sama user id
   stat(dir, &info);
//Untuk mengambil status dari file
        char mode[] = "0777"; 
        //mode string yang menyimpan kode permission 777, syntax untuk ganti 0777 
        //0 = no permission, 7 = read, write, and execute
        int a;
        a = strtol(mode, 0, 8);
        //strtol = string to long long untuk mengubah string menjadi octal karena permission bacanya octal bukan desimal
        chmod(dir, a); 
        //Chmod adalah singkatan dari change mode yang digunakan untuk menambah dan mengurangi ijin pemakai untuk mengakses file atau direktori
        //Jadi mengganti permission file di dir menjadi 777
        struct passwd *pw;
        struct group  *gr;
        pw = getpwuid(info.st_uid); 
        gr = getgrgid(info.st_gid);
        // Untuk mendapatkan pw yaitu user id
        // Untuk mendapatkan gr yaitu group id
    
    if(strcmp(gr->gr_name,"www-data")==0 && strcmp(pw->pw_name, "www-data")==0)
    // Habis mendapatkan group id lalu mengambil group name dam membandingkan file tersebut apakah sama dengan www-data
    // Habis mendapatkan user id lalu mengambil user name dan membandingkan file tersebut sama dengan www-data
    { 
        remove("/home/insane/hatiku/elen.ku");
    }
    sleep(3);
    // proses berjalan selama 3 detik sekali
  } exit(EXIT_SUCCESS);
}

/*Untuk menjalankan program soal 2 dengan cara 
melakukan compile terlebih dahulu pada code soal2.c lalu
change owner elen.ku menjadi www-data dengan 
sudo chown www-data:www-data elen.ku
