#include <stdio.h>
#include <stdlib.h>

#include "status_events.h"
#include "modules.h"
#include "levels.h"
#include "modules_db.h"
#include "utils.h"
#include "shared.h"

int main() {
    FILE* file = NULL;
    char* filename = NULL;

    if (create_events_index() == 0 && create_level_index() == 0 && create_module_index() == 0) {
        int stop = 0;
        do {
            int main_option;
            operations_list_message();
            if (read_main_option(&main_option) == 0) {
                int option;
                if (main_option == 1) {
                    if (choose_and_open(&file, &filename, "rb", &option) == 0) {
                        if (handle_select(file, option) == ERR) {
                            handle_error();
                        }
                    } else {
                        handle_error();
                    }
                } else if (main_option == 2) {
                    if (choose_and_open(&file, &filename, "ab", &option) == 0) {
                        if (handle_insert(file, filename, option) == ERR) {
                            handle_error();
                        }
                    } else {
                        handle_error();
                    }
                } else if (main_option == 3) {
                    if (choose_and_open(&file, &filename, "rb+", &option) == 0) {
                        if (handle_update(file, option) == ERR) {
                            handle_error();
                        }
                    } else {
                        handle_error();
                    }
                } else if (main_option == 4) {
                    file = fopen(MODULES, "rb+");
                    if (file != NULL) {
                        printf("> Insert id's of record to delete(in case of many id's only first counts): ");
                        delete(file, 1);
                    } else {
                        handle_error();
                    }
                } else if (main_option == 5) {
                    if (option_5(file) != 0) {
                        handle_error();
                    }
                } else if (main_option == 6) {
                    file = fopen(MODULES, "rb+");
                    if (file != NULL) {
                        printf("> Insert id's of records to delete: ");
                        delete(file, 0);
                    } else {
                        handle_error();
                    }
                } else if (main_option == 7) {
                    if (option_7(file) != 0) {
                        handle_error();
                    }
                } else if (main_option == 8) {
                    if (option_8(file) != 0) {
                        handle_error();
                    }
                } else if (main_option == 9) {
                    if (option_9(file) != 0) {
                        handle_error();
                    }
                } else {  // main_option == 10
                    stop = 1;
                }
            } else {
                handle_error();
            }
            close_file(&file);
        } while (!stop);

        close_file(&file);

        printf(quest_completed(file) ? "AI was defeated\n" : "AI won\n");
    } else {
        printf("Error while creating index files\n");
    }

    return 0;
}

int option_8(FILE* file) {
    int return_value = 0;

    printf("> Insert module id: ");
    int size;
    int* id = empty_or_positive_array(&size);
    if (id != NULL) {
        file = fopen(MODULES, "rb+");
        if (file != NULL) {
            module dest = read_record_from_modules_file(file, *id);
            printf("> Insert level id: ");
            int* level = empty_or_positive_array(&size);
            if (level != NULL) {
                printf("> Insert cell id: ");
                int* cell = empty_or_positive_array(&size);
                if (cell != NULL) {
                    dest.level_id = *level;
                    dest.cell_id = *cell;
                    modules_insert_no_input(file, &dest, id, 1);
                    free(cell);
                } else {
                    return_value = ERR;
                }
                free(level);
            } else {
                return_value = ERR;
            }
        } else {
            return_value = ERR;
        }
        free(id);
    } else {
        return_value = ERR;
    }

    return return_value;
}

void set_protected_for_id(FILE* file, const int* id) {
    int events_size = get_records_count_in_events_file(file);
    int last_id = read_record_from_events_file(file, events_size - 1).id;

    status_event *first = new_event(last_id + 1, *id, 0);
    status_event *second = new_event(last_id + 2, *id, 1);
    status_event *third = new_event(last_id + 3, *id, 20);

    write_event_in_file(file, first, events_size);
    write_event_in_file(file, second, events_size + 1);
    write_event_in_file(file, third, events_size + 2);

    free(first);
    free(second);
    free(third);
}

int option_7(FILE* file) {
    int return_value = 0;

    printf("> Insert module id: ");
    int size;
    int* id = empty_or_positive_array(&size);
    if (id != NULL) {
        file = fopen(EVENTS, "rb+");
        if (file != NULL) {
            set_protected_for_id(file, id);
        } else {
            return_value = ERR;
        }
    }
    clear_ints(&id);

    return return_value;
}

int* actual_statuses(FILE* file, int* events_size) {
    int* statuses = NULL;
    file = fopen(EVENTS, "rb");
    if (file != NULL) {
        *events_size = get_records_count_in_events_file(file);
        statuses = (int*) calloc(*events_size, sizeof(int));
        if (statuses != NULL) {
            for (int i = 0; i < *events_size; ++i) {
                statuses[i] = -1;
            }
            for (int i = 0; i < *events_size; ++i) {
                status_event temp = read_record_from_events_file(file, i);
                if (temp.module_id < *events_size) {
                    statuses[temp.module_id] = temp.new_status;
                }
            }
        }
        fclose(file);
    }
    return statuses;
}

int option_5(FILE* file) {
    int return_code = 0;

    int events_size;
    int* statuses = actual_statuses(file, &events_size);
    if (statuses != NULL) {
        file = fopen(MODULES, "rb");
        if (file != NULL) {
            int modules_size = get_records_count_in_modules_file(file);
            for (int i = 0; i < modules_size; ++i) {
                module temp = read_record_from_modules_file(file, i);
                if (temp.id < events_size && statuses[temp.id] == 1) {
                    printf("%d %s %d %d %d\n", temp.id, temp.name,
                           temp.level_id, temp.cell_id, temp.deleted);
                }
            }
        } else {
            return_code = ERR;
        }
        free(statuses);
    } else {
        return_code = ERR;
    }

    return return_code;
}

int quest_completed(FILE* file) {
    int return_value = 1;

    int events_size;
    int* statuses = actual_statuses(file, &events_size);
    if (statuses != NULL) {
        int count = 0;
        for (int i = 0; i < events_size; ++i) {
            if (statuses[i] == 1) {
                ++count;
            }
        }
        if (count == 1 && statuses[0] == 20) {
            file = fopen(MODULES, "rb");
            if (file != NULL) {
                int modules_size = get_records_count_in_modules_file(file);
                count = 0;
                for (int i = 0; i < modules_size; ++i) {
                    if (read_record_from_modules_file(file, i).deleted == 0) {
                        ++count;
                    }
                }
                module main_module = read_record_from_modules_file(file, 0);
                if (count == 1 && main_module.deleted == 0 &&
                    main_module.level_id == 1 && main_module.cell_id == 1) {
                    file = fopen(EVENTS, "rb");
                    if (file != NULL) {
                        int found = 0;
                        int i;
                        for (i = events_size - 1; !found && i >= 0; --i) {
                            status_event temp = read_record_from_events_file(file, i);
                            if (temp.module_id == 0 && temp.new_status == 0) {
                                found = 1;
                            }
                        }
                        if (found) {
                            if (read_record_from_events_file(file, i + 1).new_status == 1 &&
                                read_record_from_events_file(file, i + 2).new_status == 20) {
                                close_file(&file);
                                file = fopen(LEVELS, "rb");
                                if (file != NULL) {
                                    int ind = find_level_index(file, 1);
                                    if (read_record_from_levels_file(file, ind).security_flag != 1) {
                                        return_value = 0;
                                    }
                                } else {
                                    return_value = 1;
                                }
                            } else {
                                return_value = 0;
                            }
                        } else {
                            return_value = 0;
                        }
                    } else {
                        return_value = 0;
                    }
                } else {
                    return_value = 0;
                }
            } else {
                return_value = 0;
            }
            close_file(&file);
        } else {
            return_value = 0;
        }
    } else {
        return_value = 0;
    }
    clear_ints(&statuses);

    return return_value;
}

int option_9(FILE* file) {
    int return_code = 0;

    file = fopen(LEVELS, "rb+");
    if (file != NULL) {
        int size;
        printf("> Insert level id: ");
        int* id = empty_or_positive_array(&size);
        if (id != NULL) {
            int ind = find_level_index(file, *id);
            if (ind != -1) {
                level dest = read_record_from_levels_file(file, ind);
                dest.security_flag = 1;
                levels_insert_no_input(file, &dest, id, 1);
            } else {
                return_code = ERR;
            }
            free(id);
        } else {
            return_code = ERR;
        }
    } else {
        return_code = ERR;
    }

    return return_code;
}

int handle_update(FILE* file, int option) {
    int return_value = 0;

    printf("> Insert id of record: ");
    int size;
    int* number = empty_or_positive_array(&size);
    if (number != NULL) {
        if (option == 1) {
            module* temp = NULL;
            input_module(&temp);
            if (temp != NULL) {
                modules_insert_no_input(file, temp, number, size);
                free(temp);
            } else {
                return_value = ERR;
            }
        } else if (option == 2) {
            level* temp = NULL;
            input_level(&temp);
            if (temp != NULL) {
                levels_insert_no_input(file, temp, number, size);
                free(temp);
            } else {
                return_value = ERR;
            }
        } else {  // option == 3
            status_event* temp = NULL;
            input_event(&temp);
            if (temp != NULL) {
                events_insert_no_input(file, temp, number, size);
                free(temp);
            } else {
                return_value = ERR;
            }
        }
    } else {
        return_value = ERR;
    }
    clear_ints(&number);

    return return_value;
}

int handle_insert(FILE* file, char* filename, int option) {
    int return_value = 0;

    if (option == 1) {
        if (modules_insert(file, filename) == ERR) {
            return_value = ERR;
        }
    } else if (option == 2) {
        if (levels_insert(file, filename) == ERR) {
            return_value = ERR;
        }
    } else {  // option == 3
        if (events_insert(file, filename) == ERR) {
            return_value = ERR;
        }
    }

    return return_value;
}

int handle_select(FILE* file, int option) {
    int return_value = 0;

    int* result = NULL;
    if (option == 1) {
        result = handle_modules_output(file, 0);
        if (result == NULL) {
            return_value = ERR;
        }
    } else if (option == 2) {
        result = handle_levels_output(file);
        if (result == NULL) {
            return_value = ERR;
        }
    } else {  // option == 3
        result = handle_events_output(file);
        if (result == NULL) {
            return_value = ERR;
        }
    }
    clear_ints(&result);

    return return_value;
}

void handle_error() {
    printf("n/a\n");
}

void operations_list_message() {
    printf("\nPlease choose one operation:\n"
           "\t1. SELECT\n"
           "\t2. INSERT\n"
           "\t3. UPDATE\n"
           "\t4. DELETE\n"
           "\t5. Get all active additional modules (last module status is 1)\n"
           "\t6. Delete modules by ids\n"
           "\t7. Set protected mode for module by id\n"
           "\t8. Move module by id to specified memory level and cell\n"
           "\t9. Set protection flag of the specified memory level\n"
           "\t10. Exit\n> ");
}

int read_main_option(int* option) {
    char sym;
    int return_value = 0;
    int count = scanf("%d%c", option, &sym);
    if (count != 2 || sym != '\n') {
        flush_stdin();
        return_value = ERR;
    } else if (*option < 1 || *option > 10) {
        return_value = ERR;
    }
    return return_value;
}
