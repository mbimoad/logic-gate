#include <stdio.h>

// Fungsi gerbang logika
int andGate(int a, int b) {
    return a && b;
}

int orGate(int a, int b) {
    return a || b;
}

int nandGate(int a, int b) {
    return !(a && b);
}

int norGate(int a, int b) {
    return !(a || b);
}

int xorGate(int a, int b) {
    return a != b;
}

int xnorGate(int a, int b) {
    return a == b;
}

int notGate(int a) {
    return !a;
}

int i,j;

int main() {
    // AMBIL INPUTAN DARI FILE EXTTERNAL
    // EXAMPLE inputs[1][3] = 1
    FILE *file = fopen("input.txt", "r");
    int inputs[16][4];
    for (i = 0; i < 16; i++) {fscanf(file, "%d %d %d %d", &inputs[i][0], &inputs[i][1], &inputs[i][2], &inputs[i][3]);}
    fclose(file);
    
    

    // Buka file untuk menulis output
    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Gagal membuka output.txt\n");
        return 1;
    }

    // Header untuk output
    fprintf(outputFile, "A | B | C | D | E/0 | E/1 | F/0 | F/1 | G/0 | G/1 | H/0 | H/1 | I/0 | I/1 | J/0 | J/1 | K/0 | K/1 | Y/0 | Y/1 | Z/0 | Z/1 | ou1 | ou2 |index\n");
    fprintf(outputFile, "--|---|---|---|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-------");
    
     // Variabel untuk menyimpan hasil gerbang logika
    int result[16][16];
    
    
    // Menghitung hasil gerbang logika
    for (i = 0; i < 16; i++) {
		// Input
        result[i][0] = inputs[i][0];          				  // A
		result[i][1] = inputs[i][1];          				  // B
		result[i][2] = inputs[i][2];          				  // C
		result[i][3] = inputs[i][3];          				  // D
		
		// Logic Gate
		result[i][4] = andGate(inputs[i][0], inputs[i][1]);   // E	
		result[i][5] = orGate(inputs[i][1],inputs[i][2]);     // F
		result[i][6] = norGate(inputs[i][2],inputs[i][3]);    // G
		result[i][7] = nandGate(result[i][4], result[i][5]);  // H
		result[i][8] = notGate(result[i][5]); 			 	  // I
		result[i][9]  = xorGate(result[i][6], result[i][5]);  // J
		result[i][10] = xnorGate(result[i][7], result[i][9]); // K
		
		// Output
		result[i][11] = result[i][9];  // Y 
		result[i][12] = result[i][10]; // Z
		result[i][13] = result[i][11]; // ou1
		result[i][14] = result[i][12]; // ou2
		result[i][15] = i;			   // Index
    }
    

    
    // Menulis output ke file
    for (i = 0; i < 16; i++) {
    	// Input ABCD
        fprintf(outputFile, "\n%d | %d | %d | %d |", inputs[i][0], inputs[i][1], inputs[i][2], inputs[i][3]);
        
        
        // Coba modifikasi script nya disini JIKA TRUE Maka tambahkan v di /1, jika false tambahkan di /0
        for (j = 4; j <= 12; j++) {
	        if (result[i][j] == 1) {
	            fprintf(outputFile, "     |  v  |");
	        } else {
	            fprintf(outputFile, "     |     |");
	        }
	    }	
	    
	    for (j = 13; j <= 14; j++) {
	        if (result[i][j] == 1) {
	            fprintf(outputFile, "  1  |");
	        } else {
	            fprintf(outputFile, "  0  |");
	        }
	    }	
	    
        fprintf(outputFile, "  %d  |", result[i][15]);
        
    }
    
    
    // Penguji test vector minimum
    int test_vectors[4] = {5, 1, 4, 10};
    fprintf(outputFile, "\n\nPENGUJIAN TEST VECTOR MINIMUM\n");
    fprintf(outputFile, "Line | Unique Total Fault | Total Fault Coverage | Test Vector\n");
    int total_fault_coverage = 0;
    for (i = 0; i < 4; i++) {
        int unique_faults = 0;
        for (j = 0; j < 16; j++) {
            if (result[j][test_vectors[i]] == 1) {
                unique_faults++;
            }
        }
        total_fault_coverage += unique_faults;
        fprintf(outputFile, "%-4d | %-18d | %-20d | %-10d\n", test_vectors[i] + 1, unique_faults, total_fault_coverage, test_vectors[i]);
    }

    fprintf(outputFile, "\nTotal Test Vector: %d\n", 4);
    fprintf(outputFile, "Fault Coverage: %.2f%%\n", (float)total_fault_coverage / (16 * 16) * 100);
    
    // Tutup file output
    fclose(outputFile);
    printf("Output telah berhasil ditulis ke output.txt\n");
    return 0;
}

