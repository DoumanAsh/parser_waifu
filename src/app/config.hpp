#pragma once

#include <string>

#include <boost/filesystem.hpp>

namespace app {
    /**
     * Configuration
     */
    class Config {
        public:
            /**
             * @constructor
             *
             * Constructs config and stores filesystem::initial_path()
             * Due to that it would be wise to create config as the first thing.
             *
             * @param[in] app_dir Directory to store configuration.
             */
            explicit Config(const std::string& app_dir);

            /**
             * Saves config, if required.
             *
             * @note It handles any exception inside
             */
            ~Config();

            /**
             * Saves current config
             *
             * @throws exception As it uses file system there might be exceptions :P
             */
            void save();

            /**
             * Same as save() but performs saving only if there are pending changes.
             */
            void save_if();

        private:
            ///Determines if config has been changed.
            bool is_changed = false;
            ///Application directory. Contains also config.
            boost::filesystem::path app_dir;
            ///Configuration file path.
            boost::filesystem::path config_path;
    };
}
