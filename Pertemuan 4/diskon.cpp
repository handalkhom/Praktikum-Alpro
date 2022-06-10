#include <iostream>
using namespace std;

//void totalHarga (int hargaSatuan, int jumlahBarang, int diskon);
void totalHarga (int hargaSatuan, int jumlahBarang, int diskon){
	int hargaAwal = hargaSatuan * jumlahBarang;
	diskon = hargaAwal*diskon/100;
	int hargaAkhir = hargaAwal - diskon;
	cout << "Harga Satuan   = Rp." << hargaSatuan << endl;
	cout << "Jumlah Barang  = " << jumlahBarang << endl;
	cout << "Harga Awal     = Rp." << hargaAwal << endl;
	cout << "Total Diskon   = Rp." << diskon << endl;
	cout << "-------------------------------------" << endl;
	cout << "Total Harga    = Rp." << hargaAkhir << endl;
}

int main (){

totalHarga (10000, 10, 10);
	
	return 0;
}


