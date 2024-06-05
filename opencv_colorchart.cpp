#include <opencv2/opencv.hpp>

using namespace cv;

int create_mat_image(Mat &image) {
	const int width = image.cols;         // 画像の幅
    const int height = image.rows;        // 画像の高さ
    const int band_height = height / 12;  // 各色のバンドの高さ
    const int segment_width = width / 16; // 横方向の色の切り替わりポイント
    const int num_segments = 15;          // セグメントの総数

    // 各セグメントの色の値を事前に計算して配列に格納
    std::vector<uchar> segment_values(num_segments + 1);
    for (int i = 0; i <= num_segments; ++i) {
        segment_values[i] = static_cast<uchar>(255 * (i / static_cast<float>(num_segments)));
    }
    
     // 画像の各ピクセルに色を設定
    for (int y = 0; y < height; ++y) {
        Vec3b *row = image.ptr<Vec3b>(y); // 現在の行へのポインタ
        int band_index = y / band_height; // 現在の行が属するバンドのインデックス
        bool is_upper_half = (band_index < 6); // 上半分かどうかを判定

        for (int x = 0; x < width; ++x) {
            int segment_index = x / segment_width;       // 現在の列が属するセグメントのインデックス
            uchar value = segment_values[segment_index]; // セグメントに基づく色の値

            // 初期値は白に設定
            uchar red = 255, green = 255, blue = 255;

            // 下半分のバンドでは黒に設定
            if (!is_upper_half) {
                red = 0;
                green = 0;
                blue = 0;
            }

            // バンドのインデックスに応じて、RGB値を設定
            switch (band_index % 12) {
            case 0: red = value; break;
            case 1: green = value; break;
            case 2: blue = value; break;
            case 3: red = green = value; break;
            case 4: red = blue = value; break;
            case 5: green = blue = value; break;
            case 6: green = blue = value; break;
            case 7: red = blue = value; break;
            case 8: red = green = value; break;
            case 9: blue = value; break;
            case 10: green = value; break;
            case 11: red = value; break;
            }
            // 現在のピクセルに色を設定
            row[x] = Vec3b(blue, green, red);
        }
    }

    return 0;
}

int main() {
    const int width = 1280;
    const int height = 720;
    Mat image(height, width, CV_8UC3, Scalar(255, 255, 255));
    create_mat_image(image);

    imshow("Color Chart", image);
    imwrite("out.jpg", image);
    waitKey(0);

    return 0;
}

