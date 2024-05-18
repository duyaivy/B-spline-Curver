#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Mở tệp để đọc và ghi
    FILE *file = fopen("NURBS_data.txt", "r+");
    if (file == NULL) {
        perror("Lỗi khi mở tệp");
        return EXIT_FAILURE;
    }

    // Tìm vị trí ngay sau chuỗi "   ["
    char target[] = "   [";
    char buffer[256];
    long pos = 0;
    int found = 0;
    long line_start_pos = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        char *ptr = strstr(buffer, target);
        if (ptr != NULL) {
            line_start_pos = ftell(file) - strlen(buffer);
            pos = line_start_pos + (ptr - buffer) + strlen(target);
            found = 1;
            break;
        }
    }

    if (found) {
        // Di chuyển con trỏ tệp đến vị trí ngay sau "   ["
        fseek(file, pos, SEEK_SET);

        // Xuống dòng
        fputs("\n", file);

        // Lấy vị trí đầu dòng mới (dòng ngay sau "   [\n")
        long new_line_start_pos = ftell(file);

        // Đọc phần còn lại của tệp sau dòng đó để xóa dòng hiện tại
        fseek(file, new_line_start_pos, SEEK_SET);
        long end_pos = new_line_start_pos;
        while (fgetc(file) != '\n' && !feof(file)) {
            end_pos++;
        }

        // Ghi đè dòng đó bằng khoảng trắng để xóa dòng
        fseek(file, new_line_start_pos, SEEK_SET);
        for (long i = new_line_start_pos; i < end_pos; i++) {
            fputc(' ', file);
        }

        // Di chuyển con trỏ tệp trở lại vị trí đầu dòng
        fseek(file, new_line_start_pos, SEEK_SET);

        // In từ 1 đến 10 vào tệp
        for (int i = 1; i <= 10; i++) {
            fprintf(file, "%d ", i);
        }
        fprintf(file, "\n"); // Xuống dòng sau khi in số
    } else {
        printf("Không tìm thấy chuỗi '   [' trong tệp\n");
    }

    // Di chuyển con trỏ tệp đến ký tự thứ 55
    fseek(file, 54, SEEK_SET); // Di chuyển đến ký tự thứ 55 (chỉ số 54)

    // Xóa dòng chứa ký tự thứ 55
    long line_start_pos_55 = ftell(file);
    while (line_start_pos_55 > 0 && fgetc(file) != '\n') {
        fseek(file, --line_start_pos_55, SEEK_SET);
    }
    if (line_start_pos_55 != 0) {
        fseek(file, line_start_pos_55 + 1, SEEK_SET); // Di chuyển đến đầu dòng
    }

    long end_pos_55 = line_start_pos_55;
    while (fgetc(file) != '\n' && !feof(file)) {
        end_pos_55++;
    }
    fseek(file, line_start_pos_55 + 1, SEEK_SET);
    for (long i = line_start_pos_55 + 1; i < end_pos_55; i++) {
        fputc(' ', file); // Ghi đè các ký tự bằng khoảng trắng
    }

    // Di chuyển con trỏ tệp trở lại vị trí đầu dòng
    fseek(file, line_start_pos_55 + 1, SEEK_SET);

    // Ghi "mạng lỏ" tại vị trí đó
    fprintf(file, "mạng lỏ");

    // Đóng tệp
    fclose(file);
    return EXIT_SUCCESS;
}
