# NetworkEvents plugin
This reposiory contains the following first party plugins developed by Open Ephys that make use of the [0MQ library](http://zeromq.org/):

**NetworkEvents**: A plugin that allows controlling basic functions of the GUI such as recording toggle, as well as sending custom events via network using 0MQ. For more information, go to our [wiki](https://open-ephys.atlassian.net/wiki/spaces/OEW/pages/23265310/Network+Events) and find out how to use this plugin.

## Installation
### Installing the 0MQ library
For windows and linux, the required files are already included for the plugin
We have detailed instructions on our wiki on how to install the 0MQ for [macOS](https://open-ephys.atlassian.net/wiki/spaces/OEW/pages/491555/macOS).

### Building the plugins
Building the plugins requires [CMake](https://cmake.org/). Detailed instructions on how to build open ephys plugins with CMake can be found in [our wiki](https://open-ephys.atlassian.net/wiki/spaces/OEW/pages/1259110401/Plugin+CMake+Builds).
 