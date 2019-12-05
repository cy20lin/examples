#include <iostream>
#include <memory>
#include <thread>

#include <Open3D/Open3D.h>

// A simplified version of examples/Cpp/Visualizer.cpp to demonstrate linking
// an external project to Open3D.
int main(int argc, char *argv[]) {
    using namespace open3d;

    utility::SetVerbosityLevel(utility::VerbosityLevel::Debug);
    if (argc < 2) {
        utility::LogInfo("Open3D {}\n", OPEN3D_VERSION);
        utility::LogInfo("\n");
        utility::LogInfo("Usage:\n");
        utility::LogInfo("    > simple_pointcloud_visualizer [filename]\n");
        // CI will execute this file without input files, return 0 to pass
        return 0;
    }

    auto cloud_ptr = std::make_shared<geometry::PointCloud>();
    if (io::ReadPointCloud(argv[1], *cloud_ptr)) {
        utility::LogInfo("Successfully read {}\n", argv[1]);
    } else {
        utility::LogError("Failed to read {}\n\n", argv[1]);
        return 1;
    }
    cloud_ptr->NormalizeNormals();

    visualization::Visualizer v;
    bool success = v.CreateVisualizerWindow("simple_pointcloud_visualizer");
    if (success) {
        v.AddGeometry(cloud_ptr);
        v.Run();
    } 
    utility::LogInfo("End of the test.\n");
    return 0;
}
