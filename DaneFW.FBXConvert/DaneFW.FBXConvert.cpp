#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <bitset>

#include <fbxsdk.h>

#pragma region bitToAscii
char bitToAscii(const std::string& bits) {
    std::bitset<8> b(bits);
    return static_cast<char>(b.to_ulong());
}

std::string readFirstEightBits(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    std::string result;

    if (file.is_open()) {
        char byte;
        if (file.get(byte)) {
            std::bitset<8> bits(static_cast<unsigned char>(byte));
            result = bits.to_string();
        }
        file.close();
    }
    else {
        std::cerr << "Không thể mở file: " << filename << std::endl;
    }

    return result;
}
#pragma endregion

class fbxlib {
private:
    std::string UrlInput;
    std::string UrlOutput;

public:
    const std::string& GetUrlInput() const {
        return UrlInput;
    }
    void SetUrlInput(std::string& url) {
        UrlInput = url;
    }
    const std::string& GetUrlOutput() const {
        return UrlOutput;
    }
    void SetUrlOutput(std::string& url) {
        UrlOutput = url;
    }

    void fbxconvertBinaryToAscii() {
        FbxManager* fbxManager = FbxManager::Create();
        FbxIOSettings* ioSettings = FbxIOSettings::Create(fbxManager, IOSROOT);

        FbxImporter* importer = FbxImporter::Create(fbxManager, "");
        fbxManager->SetIOSettings(ioSettings);

        if (!importer->Initialize(GetUrlInput().c_str(), -1, fbxManager->GetIOSettings())) {
            printf("Failed to initialize importer: %s\n", importer->GetStatus().GetErrorString());
            return;
        }

        FbxScene* scene = FbxScene::Create(fbxManager, "myScene");

        // Import dữ liệu vào scene
        importer->Import(scene);
        importer->Destroy(); // Đã xong import, không cần importer nữa

        // Tạo exporter
        FbxExporter* exporter = FbxExporter::Create(fbxManager, "");

        // Thiết lập để export dưới dạng ASCII
        int fileFormat = fbxManager->GetIOPluginRegistry()->FindWriterIDByDescription("FBX ascii (*.fbx)");
        if (!exporter->Initialize(GetUrlOutput().c_str(), fileFormat, fbxManager->GetIOSettings())) {
            printf("Failed to initialize exporter: %s\n", exporter->GetStatus().GetErrorString());
            return;
        }

        // Export scene dưới dạng ASCII
        exporter->Export(scene);
        exporter->Destroy(); // Xong việc export, hủy exporter

        // Dọn dẹp bộ nhớ
        scene->Destroy();
        ioSettings->Destroy();
        fbxManager->Destroy();
    }

};

int main()
{
    std::string input = "C:\\Users\\admin\\Desktop\\HumanModel.fbx";
    std::string output = "C:\\Users\\admin\\Desktop\\HumanModelOutput.fbx";
    fbxlib* fbx = new fbxlib();
    fbx->SetUrlInput(input);
    fbx->SetUrlOutput(output);
    fbx->fbxconvertBinaryToAscii();
    return 0;
}
