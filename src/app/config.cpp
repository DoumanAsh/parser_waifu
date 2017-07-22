#include <iostream>
#include <exception>

#include <boost/filesystem/fstream.hpp>

#include "config.hpp"
#include "../ui/message.hpp"

using namespace app;
namespace fs = boost::filesystem;

Config::Config(const std::string& app_dir) : app_dir(app_dir) {
    this->config_path = this->app_dir / "pw.toml";
    this->config_path.make_preferred(); //By default boost::filesystem will not convert paths to system one.

}

void Config::save() {
    this->is_changed = false;

    //boost filesystem streams are basically std streams with exception of constructors accepting paths
    fs::ofstream config(this->config_path);

    config << "TEST\n";
}

void Config::save_if() {
    if (this->is_changed) this->save();
}

Config::~Config() {
    try {
        this->save();
    }
    catch (const std::exception& exception) {
        ui::message::Pop().title("Save config")
                          .text("Unable to save config file")
                          .details(exception.what())
                          .type(ui::message::Pop::Type::Error)
                          .run();
    }
}
