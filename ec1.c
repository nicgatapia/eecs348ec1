#include <stdio.h>
#include <stdbool.h>

#define NUM_DEPTS 5
#define NUM_PROGS 5

int main() {
    int dept_prefs[NUM_DEPTS][NUM_PROGS];
    int prog_prefs[NUM_PROGS][NUM_DEPTS];
    bool prog_assigned[NUM_PROGS] = {false};
    int prog_assignment[NUM_DEPTS];
    
    // Read input from file
    FILE *input_file = fopen("input.txt", "r");
    for (int i = 0; i < NUM_DEPTS; i++) {
        for (int j = 0; j < NUM_PROGS; j++) {
            fscanf(input_file, "%d", &dept_prefs[i][j]);
        }
    }
    for (int i = 0; i < NUM_PROGS; i++) {
        for (int j = 0; j < NUM_DEPTS; j++) {
            fscanf(input_file, "%d", &prog_prefs[i][j]);
        }
    }
    fclose(input_file);
    
    // Assign Programmers to Departments
    for (int i = 0; i < NUM_DEPTS; i++) {
        for (int j = 0; j < NUM_PROGS; j++) {
            int prog_index = dept_prefs[i][j] - 1;
            if (!prog_assigned[prog_index]) {
                prog_assigned[prog_index] = true;
                prog_assignment[i] = prog_index + 1;
                break;
            } else {
                int current_dept = 0;
                int pref_index = 0;
                while (prog_prefs[prog_index][pref_index] != i + 1) {
                    int dept_index = prog_prefs[prog_index][pref_index] - 1;
                    if (dept_index == i) {
                        current_dept = pref_index;
                        break;
                    }
                    pref_index++;
                }
                int other_dept_index = prog_assignment[current_dept] - 1;
                if (other_dept_index > i) {
                    prog_assignment[i] = prog_index + 1;
                    prog_assignment[current_dept] = 0;
                    prog_assigned[prog_index] = true;
                    prog_assigned[other_dept_index] = false;
                    break;
                }
            }
        }
    }
    
    // Print results
    for (int i = 0; i < NUM_DEPTS; i++) {
        printf("Department %d is assigned Programmer %d\n", i + 1, prog_assignment[i]);
    }
    
    return 0;
}