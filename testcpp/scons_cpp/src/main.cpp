#include <NxAPI.h>
#include <stdio.h>

// PPM格式文件存储
static void writePPM(const NxRGBA *image, int xres, int yres, const char *filename)
{
    const float gammaValue = 1.0f / 2.2f;
    FILE *fp = fopen(filename, "wb");
    fprintf(fp, "P3\n");
    fprintf(fp, "%d %d\n", xres, yres);
    fprintf(fp, "255\n");
    for (int y = 0; y < yres; ++y)
    {
        for (int x = 0; x < xres; ++x)
        {
            int pixelIndex = (yres - 1 - y) * xres + x;
            NxByte r = (NxByte)(MIN(1.0f, powf(image[pixelIndex].m[0], gammaValue)) * 255.0f);
            NxByte g = (NxByte)(MIN(1.0f, powf(image[pixelIndex].m[1], gammaValue)) * 255.0f);
            NxByte b = (NxByte)(MIN(1.0f, powf(image[pixelIndex].m[2], gammaValue)) * 255.0f);
            fprintf(fp, "%d %d %d ", (int)r, (int)g, (int)b);
        }
    }
    fprintf(fp, "\n");
    fclose(fp);
}

int main()
{
    //创建NxWorld
    struct NxWorld *world = NxCreateWorld();

    //设置渲染选项
    struct NxNode *opt = NxCreateNode(world, NX_UTF8("options"));
    NxNodeSet(opt, NX_UTF8("name"), NX_UTF8("renderOptions"));
    constexpr int xres = 960;
    constexpr int yres = 540;
    NxNodeSet(opt, NX_UTF8("xres"), (const NxUint[]){xres});
    NxNodeSet(opt, NX_UTF8("yres"), (const NxUint[]){yres});
    NxNodeSet(opt, NX_UTF8("camera"), NX_UTF8("perspShape"));

    //创建并设置相机
    struct NxMat4 camera_mat = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f};
    struct NxNode *cam = NxCreateNode(world, NX_UTF8("persp_camera"));
    NxNodeSet(cam, NX_UTF8("name"), NX_UTF8("perspShape"));
    NxNodeSet(cam, NX_UTF8("matrix"), NxCreateArray(world, "mat4", 1, 1, &camera_mat));
    float camera_fovs[1] = {45};
    NxNodeSet(cam, NX_UTF8("fov"), NxCreateArray(world, "float", 1, 1, &camera_fovs[0]));

    //创建平面
    struct NxNode *plane = NxCreateNode(world, NX_UTF8("polymesh"));
    NxNodeSet(plane, NX_UTF8("name"), NX_UTF8("planeName"));
    //顶点个数
    constexpr int vcount = 4;
    //面数
    constexpr int fcount = 1;
    //顶点索引个数
    constexpr int vtcount = 4;
    //该平面仅有的一个面由4个顶点来表示
    NxUint mesh1_nsides[fcount]{4};
    //顶点索引数组
    constexpr NxUint mesh1_vidxs[4 * fcount] = {0, 1, 3, 2};
    //顶点数组
    constexpr float mesh1_vlist[vcount * 3] = {
        -500.000000, -0.000000, 500.000000,
        500.000000, -0.000000, 500.000000,
        -500.000000, 0.000000, -500.000000,
        500.000000, 0.000000, -500.000000};
    // uv索引数组
    constexpr NxUint mesh1_uvidxs[4 * fcount] = {0, 1, 3, 2};
    // uv数组
    constexpr float mesh1_uvlist[vtcount * 2] = {
        0.000000, 0.000000,
        1.000000, 0.000000,
        0.000000, 1.000000,
        1.000000, 1.000000};
    //平面的位置
    struct NxMat4 plane_mat = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, -25.0f, 0.0f, 1.0f};
    //使用上述几何信息对平面进行设置
    NxNodeSet(plane, NX_UTF8("matrix"), NxCreateArray(world, "mat4", 1, 1, &plane_mat));
    NxNodeSet(plane, NX_UTF8("nsides"), NxCreateArray(world, "uint", fcount, 1, mesh1_nsides));
    NxNodeSet(plane, NX_UTF8("vidxs"), NxCreateArray(world, "uint", fcount * 4, 1, mesh1_vidxs));
    NxNodeSet(plane, NX_UTF8("vlist"), NxCreateArray(world, "vec3", vcount, 1, mesh1_vlist));
    NxNodeSet(plane, NX_UTF8("uvidxs"), NxCreateArray(world, "uint", fcount * 4, 1, mesh1_uvidxs));
    NxNodeSet(plane, NX_UTF8("uvlist"), NxCreateArray(world, "vec2", vtcount, 1, mesh1_uvlist));

    //为平面创建材质
    struct NxNode *mtl = NxCreateNode(world, NX_UTF8("material"));
    NxNodeSet(mtl, NX_UTF8("name"), NX_UTF8("material1"));
    NxNodeSet(mtl, NX_UTF8("beauty"), NX_UTF8("lambert1"));
    //创建lambert shader
    struct NxNode *shader = NxCreateNode(world, NX_UTF8("lambert"));
    NxNodeSet(shader, NX_UTF8("name"), NX_UTF8("lambert1"));
    NxNodeConnect(shader, NX_UTF8("Kd_color"), NX_UTF8("texx"), NX_UTF8("outColor"));
    //创建纹理
    struct NxNode *tex = NxCreateNode(world, NX_UTF8("file_texture"));
    NxNodeSet(tex, NX_UTF8("name"), NX_UTF8("texx"));
    NxNodeSet(tex, NX_UTF8("filename"), NX_UTF8("../chess_grid.tif"));
    //为平面赋予材质
    const char *shaderNames[2]{NX_UTF8("material1")};
    NxNodeSet(plane, NX_UTF8("shader"), NxCreateArray(world, "ustring", 1, 1, shaderNames));

    //***************************************************************************
    //创建立方体cube，并按照与plane类似的方式设置几何信息
    struct NxNode *cube = NxCreateNode(world, NX_UTF8("polymesh"));
    NxNodeSet(cube, NX_UTF8("name"), NX_UTF8("cubeName"));
    constexpr int cube_vcount = 8;
    constexpr int cube_fcount = 6;
    NxUint mesh2_nsides[cube_fcount];
    for (int i = 0; i < cube_fcount; i++)
    {
        mesh2_nsides[i] = 4;
    }
    constexpr NxUint mesh2_vidxs[4 * cube_fcount] = {
        0, 1, 3, 2,
        2, 3, 5, 4,
        4, 5, 7, 6,
        6, 7, 1, 0,
        1, 7, 5, 3,
        6, 0, 2, 4};
    constexpr float mesh2_vlist[cube_vcount * 3] = {
        -6.010446, -25.000000, 34.840702,
        34.840702, -25.000000, 6.010446,
        -6.010446, 25.000000, 34.840702,
        34.840702, 25.000000, 6.010446,
        -34.840702, 25.000000, -6.010446,
        6.010446, 25.000000, -34.840702,
        -34.840702, -25.000000, -6.010446,
        6.010446, -25.000000, -34.840702};

    struct NxMat4 cube_mat = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, -300.0f, 1.0f};
    NxNodeSet(cube, NX_UTF8("matrix"), NxCreateArray(world, "mat4", 1, 1, &cube_mat));
    NxNodeSet(cube, NX_UTF8("nsides"), NxCreateArray(world, "uint", cube_fcount, 1, mesh2_nsides));
    NxNodeSet(cube, NX_UTF8("vidxs"), NxCreateArray(world, "uint", cube_fcount * 4, 1, mesh2_vidxs));
    NxNodeSet(cube, NX_UTF8("vlist"), NxCreateArray(world, "vec3", cube_vcount, 1, mesh2_vlist));

    //为cube创建材质
    struct NxNode *mtl2 = NxCreateNode(world, NX_UTF8("material"));
    NxNodeSet(mtl2, NX_UTF8("name"), NX_UTF8("material2"));
    NxNodeSet(mtl2, NX_UTF8("beauty"), NX_UTF8("lambert2"));
    // lambert shader
    struct NxNode *shader2 = NxCreateNode(world, NX_UTF8("lambert"));
    NxNodeSet(shader2, NX_UTF8("name"), NX_UTF8("lambert2"));
    NxNodeSet(shader2, NX_UTF8("Kd_color"), (const float[]){1.0f, 0.0f, 0.0f});
    //为cube赋予材质
    shaderNames[1] = NX_UTF8("material2");
    NxNodeSet(cube, NX_UTF8("shader"), NxCreateArray(world, "ustring", 1, 1, &shaderNames[1]));

    //创建平行光源
    NxNode *light = NxCreateNode(world, NX_UTF8("distant_light"));
    NxNodeSet(light, NX_UTF8("name"), NX_UTF8("d_light"));
    struct NxMat4 light_mat = {
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f};
    NxNodeSet(light, NX_UTF8("matrix"), NxCreateArray(world, "mat4", 1, 1, &light_mat));
    NxNodeSet(light, NX_UTF8("intensity"), (const float[]){4.0f});

    //创建渲染器
    struct NxRenderer *renderer = NxCreateRenderer();
    //创建帧缓存
    const int imageBufferID = NxRenderAcquireFrameBuffer(renderer, NX_UTF8("beauty"), NULL, xres * yres, NX_FALSE);
    //渲染，并将渲染结果从帧缓存中取出
    NxRender(renderer, world);
    NxRGBA *imageBuffer = NxRenderGetFramebufferByID(renderer, imageBufferID, NULL);
    //将帧缓存中的结果保存到./cube.ppm
    writePPM(imageBuffer, xres, yres, "./cube.ppm");
    NxDeleteWorld(world);
}