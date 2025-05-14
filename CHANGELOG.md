# Changelog for Network Events Plugin

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2025-05-13

### Changed
- The plugin is now compatible with the stable GUI version 1.0.0 (API10).

## [0.3.0-dev]

### Added 
- The new `TTL Word=<word>` commands sets all TTL lines at once to the desired `uint64 <word>` value.

### Changed 
- The plugin is now only compatible with the (pre-release) GUI version 1.0 (API9).
- The Python example clients in the [`Resources/Python` (Resources/Python) folder were updated for Python 3 and the new TTL Word feature.
- Broadcasting of messages incoming via ZMQ to all other nodes is now disabled by default. It can be enabled via a toggle in the GUI.
