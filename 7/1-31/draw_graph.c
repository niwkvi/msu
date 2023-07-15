#include <stdio.h>
#include <stdlib.h>
#include "pbPlots.h"

unsigned char *DoubleArrayToByteArray(double *data, size_t length) {
    unsigned char *out;
    size_t i;

    out = (unsigned char *) malloc(sizeof(unsigned char) * length);

    for (i = 0; i < length; i++) {
        out[i] = data[i];
    }

    return out;
}

void WriteToFile(double *data, size_t dataLength, char *filename) {
    unsigned char *bytes;

    bytes = DoubleArrayToByteArray(data, dataLength);

    FILE *file = fopen(filename, "wb");
    fwrite(bytes, 1, dataLength, file);
    fclose(file);

    free(bytes);
}

double *ByteArrayToDoubleArray(unsigned char *data, size_t length) {
    double *out;
    size_t i;

    out = (double *) malloc(sizeof(double) * length);

    for (i = 0; i < length; i++) {
        out[i] = data[i];
    }

    return out;
}

// red - my solution
// blue - real solution
void draw_graph(double *xs, double *ys, double *ys_real, int n) {
    _Bool success;
    StringReference *errorMessage;
    RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
    series->xs = xs;
    series->xsLength = n;
    series->ys = ys;
    series->ysLength = n;
    series->linearInterpolation = true;
    series->lineType = L"solid";
    series->lineTypeLength = wcslen(series->lineType);
    series->lineThickness = 1;
    series->color = CreateRGBColor(1, 0, 0);

    ScatterPlotSeries *series2 = GetDefaultScatterPlotSeriesSettings();
    series2->xs = xs;
    series2->xsLength = n;
    series2->ys = ys_real;
    series2->ysLength = n;
    series2->linearInterpolation = true;
    series2->lineType = L"solid";
    series2->lineTypeLength = wcslen(series2->lineType);
    series2->lineThickness = 1;
    series2->color = CreateRGBColor(0, 0, 1);

    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->width = 600;
    settings->height = 400;
    settings->autoBoundaries = true;
    settings->autoPadding = true;
    settings->title = L"";
    settings->titleLength = wcslen(settings->title);
    settings->xLabel = L"";
    settings->xLabelLength = wcslen(settings->xLabel);
    settings->yLabel = L"";
    settings->yLabelLength = wcslen(settings->yLabel);
    ScatterPlotSeries *s[] = {series, series2};
    settings->scatterPlotSeries = s;
    settings->scatterPlotSeriesLength = 2;

    errorMessage = (StringReference *) malloc(sizeof(StringReference));
    success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);

    if (success) {
        size_t length;
        double *pngdata = ConvertToPNG(&length, imageReference->image);
        WriteToFile(pngdata, length, "graph.png");
        DeleteImage(imageReference->image);
    } else {
        fprintf(stderr, "Error: ");
        for (int i = 0; i < errorMessage->stringLength; i++) {
            fprintf(stderr, "%c", errorMessage->string[i]);
        }
        fprintf(stderr, "\n");
    }
}
