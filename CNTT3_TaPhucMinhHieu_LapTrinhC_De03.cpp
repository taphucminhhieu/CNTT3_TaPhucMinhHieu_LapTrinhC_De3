#include <stdio.h>
#include <string.h>

struct DauSach {
    int maSach;
    char tenSach[50];
    int soLuong;
    float giaBan;
};


void xoaKyTuXuongDong(char str[]) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int timKiemTheoMa(struct DauSach ds[], int n, int ma) {
    for (int i = 0; i < n; i++) {
        if (ds[i].maSach == ma) {
            return i;
        }
    }
    return -1;
}


void themDauSach(struct DauSach ds[], int *n) {
    if (*n >= 50) {
        printf("Danh sach da day\n");
        return;
    }

    int ma;
    printf("Nhap ma dau sach: ");
    scanf("%d", &ma);


    if (timKiemTheoMa(ds, *n, ma) != -1) {
        printf("Ma dau sach da ton tai\n");
        return;
    }

    ds[*n].maSach = ma;

    printf("Nhap ten dau sach: ");
    getchar();
    fgets(ds[*n].tenSach, sizeof(ds[*n].tenSach), stdin);
    xoaKyTuXuongDong(ds[*n].tenSach);


    do {
        printf("Nhap so luong ton (>= 0): ");
        scanf("%d", &ds[*n].soLuong);
        if (ds[*n].soLuong < 0) {
            printf("Loi! So luong phai lon hon hoac bang 0. Nhap lai.\n");
        }
    } while (ds[*n].soLuong < 0);


    do {
        printf("Nhap gia ban (> 0): ");
        scanf("%f", &ds[*n].giaBan);
        if (ds[*n].giaBan <= 0) {
            printf("Loi! Gia ban phai lon hon 0. Nhap lai.\n");
        }
    } while (ds[*n].giaBan <= 0);

    (*n)++;
    printf("Them dau sach thanh cong\n");
}


void hienThiDanhSach(struct DauSach ds[], int n) {
    if (n == 0) {
        printf("Danh sach rong\n");
        return;
    }

    printf("---------------------------------------------------------------------------------\n");
    printf("%-10s | %-30s | %-10s | %-12s | %-12s\n", "Ma", "Ten dau sach", "So luong", "Gia ban", "Thanh tien");
    printf("---------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        long long thanhTien = (long long)ds[i].soLuong * ds[i].giaBan;
        printf("%-10d | %-30s | %-10d | %-12.0f | %-12lld\n", 
               ds[i].maSach, ds[i].tenSach, ds[i].soLuong, ds[i].giaBan, thanhTien);
    }
    printf("---------------------------------------------------------------------------------\n");
}


void capNhatDauSach(struct DauSach ds[], int n) {
    if (n == 0) {
        printf("Danh sach rong\n");
        return;
    }

    int ma;
    printf("Nhap ma dau sach can sua: ");
    scanf("%d", &ma);

    int idx = timKiemTheoMa(ds, n, ma);
    if (idx == -1) {
        printf("Khong tim thay dau sach\n");
        return;
    }

    printf("Nhap ten dau sach moi: ");
    getchar();
    fgets(ds[idx].tenSach, sizeof(ds[idx].tenSach), stdin);
    xoaKyTuXuongDong(ds[idx].tenSach);

    do {
        printf("Nhap so luong ton moi (>= 0): ");
        scanf("%d", &ds[idx].soLuong);
        if (ds[idx].soLuong < 0) {
            printf("Loi! So luong phai lon hon hoac bang 0. Nhap lai.\n");
        }
    } while (ds[idx].soLuong < 0);

    do {
        printf("Nhap gia ban moi (> 0): ");
        scanf("%f", &ds[idx].giaBan);
        if (ds[idx].giaBan <= 0) {
            printf("Loi! Gia ban phai lon hon 0. Nhap lai.\n");
        }
    } while (ds[idx].giaBan <= 0);

    printf("Cap nhat thanh cong\n");
}


void xoaDauSach(struct DauSach ds[], int *n) {
    if (*n == 0) {
        printf("Danh sach rong\n");
        return;
    }

    int ma;
    printf("Nhap ma dau sach can xoa: ");
    scanf("%d", &ma);

    int idx = timKiemTheoMa(ds, *n, ma);
    if (idx == -1) {
        printf("Khong tim thay dau sach\n");
        return;
    }


    for (int i = idx; i < *n - 1; i++) {
        ds[i] = ds[i + 1];
    }
    (*n)--;
    printf("Xoa thanh cong\n");
}


void timKiemTheoTen(struct DauSach ds[], int n) {
    if (n == 0) {
        printf("Danh sach rong\n");
        return;
    }

    char ten[50];
    printf("Nhap ten dau sach can tim: ");
    getchar();
    fgets(ten, sizeof(ten), stdin);
    xoaKyTuXuongDong(ten);

    int count = 0;
    printf("---------------------------------------------------------------------------------\n");
    printf("%-10s | %-30s | %-10s | %-12s | %-12s\n", "Ma", "Ten dau sach", "So luong", "Gia ban", "Thanh tien");
    printf("---------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        if (strcmp(ds[i].tenSach, ten) == 0) {
            long long thanhTien = (long long)ds[i].soLuong * ds[i].giaBan;
            printf("%-10d | %-30s | %-10d | %-12.0f | %-12lld\n", 
                   ds[i].maSach, ds[i].tenSach, ds[i].soLuong, ds[i].giaBan, thanhTien);
            count++;
        }
    }
    printf("---------------------------------------------------------------------------------\n");

    if (count == 0) {
        printf("Khong tim thay dau sach\n");
    }
}


void thongKeKhoHang(struct DauSach ds[], int n) {
    if (n == 0) {
        printf("Danh sach rong\n");
        return;
    }

    double tongGiaTriKho = 0;
    int soLuongSapHet = 0;
    long long maxThanhTien = -1;
    int idxMax = 0;

    for (int i = 0; i < n; i++) {
        long long thanhTien = (long long)ds[i].soLuong * ds[i].giaBan;
        tongGiaTriKho += thanhTien;

        if (ds[i].soLuong < 5) {
            soLuongSapHet++;
        }

        if (thanhTien > maxThanhTien) {
            maxThanhTien = thanhTien;
            idxMax = i;
        }
    }

    printf("Tong gia tri kho: %.0f\n", tongGiaTriKho);
    
    printf("Cac dau sach sap het hang (so luong < 5):\n");
    for (int i = 0; i < n; i++) {
        if (ds[i].soLuong < 5) {
            printf("- Ma: %d | Ten: %s | So luong: %d\n", ds[i].maSach, ds[i].tenSach, ds[i].soLuong);
        }
    }
    printf("So dau sach sap het hang: %d\n", soLuongSapHet);

    printf("Dau sach co thanh tien lon nhat:\n");
    printf("- Ma: %d | Ten: %s | Thanh tien: %lld\n", 
           ds[idxMax].maSach, ds[idxMax].tenSach, (long long)ds[idxMax].soLuong * ds[idxMax].giaBan);
}


int main() {
    struct DauSach danhSach[50];
    int n = 0;
    int chon;

    do {
        printf("\n===== QUAN LY DAU SACH =====\n");
        printf("1. Them dau sach\n");
        printf("2. Hien thi danh sach dau sach\n");
        printf("3. Cap nhat dau sach theo ma\n");
        printf("4. Xoa dau sach theo ma\n");
        printf("5. Tim dau sach theo ten\n");
        printf("6. Thong ke kho hang\n");
        printf("0. Thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &chon);

        switch (chon) {
            case 1:
                themDauSach(danhSach, &n);
                break;
            case 2:
                hienThiDanhSach(danhSach, n);
                break;
            case 3:
                capNhatDauSach(danhSach, n);
                break;
            case 4:
                xoaDauSach(danhSach, &n);
                break;
            case 5:
                timKiemTheoTen(danhSach, n);
                break;
            case 6:
                thongKeKhoHang(danhSach, n);
                break;
            case 0:
                printf("Tam biet! Thoat chuong trinh.\n");
                break;
            default:
                printf("Chuc nang khong hop le. Vui long chon lai!\n");
        }
    } while (chon != 0);

    return 0;
}
