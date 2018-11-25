#pragma once


#include <boost/program_options.hpp>
// todo require json lib

namespace para {

class abstract_plguin
{
public:
    virtual ~abstract_plguin(){}
    virtual std::string plguin_name() const = 0;

    /**
    * @brief Perform early startup routines and register plugin indexes, callbacks, etc.
    *
    * Plugins MUST supply a method initialize() which will be called early in the application startup. This method
    * should contain early setup code such as initializing variables, adding indexes to the database, registering
    * callback methods from the database, adding APIs, etc., as well as applying any options in the @ref options map
    *
    * @param options The options passed to the application, via configuration files or command line
    */
    virtual void plugin_initialize(const boost::program_options::variables_map& options) = 0;

    /**
    * @brief Begin normal runtime operations
    *
    * Plugins MUST supply a method startup() which will be called at the end of application startup. This method
    * should contain code which schedules any tasks.
    */
    virtual void plugin_startup() = 0;

    /**
    * @brief Cleanly shut down the plugin.
    *
    * This is called to request a clean shutdown (e.g. due to SIGINT or SIGTERM).
    */
    virtual void plugin_shutdown() = 0;

    /**
    * @brief Register the application instance with the plugin.
    *
    * This is called by the framework to set the application.
    */
    virtual void plugin_set_app( application* a ) = 0;

    /**
    * @brief Fill in command line parameters used by the plugin.
    *
    * @param command_line_options All options this plugin supports taking on the command-line
    * @param config_file_options All options this plugin supports storing in a configuration file
    *
    * This method populates its arguments with any
    * command-line and configuration file options the plugin supports.
    * If a plugin does not need these options, it
    * may simply provide an empty implementation of this method.
    */
    virtual void plugin_set_program_options(
        boost::program_options::options_description& command_line_options,
        boost::program_options::options_description& config_file_options
    ) = 0;
};

}
