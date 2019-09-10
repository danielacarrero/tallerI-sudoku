#include <stdio.h>
#include <stdbool.h>
#include "utils.h"

bool has_repeated_values(size_t arr[], size_t len) {
    for (size_t i = 0; i < len; i++) {
        for(size_t j = i + 1; j < len; j++){
            if(arr[i] == arr[j]){
                return true;
            }
        }
    }

    return false;
}
