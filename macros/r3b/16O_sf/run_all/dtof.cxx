#include <iostream>
#include <cmath>
{
    double paddle_width = 2.7;
    double paddle_width_x_axis = paddle_width / cos(18. * 3.1415 / 180.);

    // double start_pos_left = -140.95 - paddle_width_x_axis;
    double start_pos_left = -142.56;
    double start_bin_left = dTOFPoint_fX->FindBin(start_pos_left);

    double next_left, next_bin_left, diff_left;
    std::cout << "LEFT:" << std::endl;
    for (int i=1; i < 5; i++){
        next_left = start_pos_left - paddle_width_x_axis;
        next_bin_left =  dTOFPoint_fX->FindBin(next_left);
        diff_left = dTOFPoint_fX -> Integral(next_bin_left, start_bin_left);

        std::cout << "Paddle from (pos/bin): " << start_pos_left << "/" << start_bin_left << " | Paddle to (pos/bin): " << next_left << "/"
        << next_bin_left << " | Counts: " << diff_left << std::endl;
        
        start_bin_left = next_bin_left;
        start_pos_left = next_left;
    } 

    // double start_pos_right = -135.695 + paddle_width_x_axis;
    double start_pos_right = -134.875;
    double start_bin_right = dTOFPoint_fX->FindBin(start_pos_right);

    double next_right, next_bin_right, diff_right;
    std::cout << "RIGHT:" << std::endl;
    for (int i=1; i < 5; i++){
        next_right = start_pos_right + paddle_width_x_axis;
        next_bin_right =  dTOFPoint_fX->FindBin(next_right);
        diff_right = dTOFPoint_fX -> Integral(start_bin_right, next_bin_right);

        std::cout << "Paddle from (pos/bin): " << start_pos_right << "/" << start_bin_right << " | Paddle to (pos/bin): " << next_right << "/"
        << next_bin_right << " | Counts: " << diff_right << std::endl;
        
        start_bin_right = next_bin_right;
        start_pos_right = next_right;
    } 
}