#include <iostream>
#include <fstream>
#include <filesystem>
#include <yaml-cpp/yaml.h>

using namespace std;

#include <string>
#include <unordered_map>

template <typename T>
using Record = std::unordered_map<std::string, T>;

struct PijamaConfig {
	struct StructureConfig {
		Record<string> base = {
			{"metadata", "${project.structure.root}/${var.feature}/feature.yaml"},
			{"todo", "${project.structure.root}/${var.feature}/todo.yaml"}
		};
		Record<string> data = {
			{"root", "${project.structure.root}/${var.feature}/data"},
			{"entity", "${project.structure.data.root}/entities"},
			{"constant", "${project.data.root}/constants"},
			{"model", "${project.structure.data.root}/models"}
		};
		Record<string> ui = {
			{"root", "${project.structure.root}/${var.feature}/ui"},
			{"page", "${project.structure.ui.root}/pages"},
			{"widget", "${project.structure.ui.root}/widgets"},
			{"component", "${project.structure.ui.root}/components"},
			{"template", "${project.structure.ui.root}/templates"}
		};
		Record<Record<string>> logic = {
			{"root", {"path", "${project.structure.root}/${var.feature}/logic"}},
			{"function", {
				{"root", "${project.structure.logic.root.path}/functions"},
				{"controllers", "${project.structure.logic.functions.root}/controllers"}
			}},
			{"class", {
				{"root", "${project.structure.logic.root}/functions"},
				{"repository", "${project.structure.logic.functions.root}/repositories"}
			}},
			{"misc", {
				{"root", "${project.structure.logic.root}/misc"}
			}}
		};
	};

	struct CommandConfig {
		Record<string> node = {
			{"start", "pijama.command.node.start"},
			{"build", "pijama.command.node.build"}
		};
	};

	struct LanguageConfig {
		Record<Record<string>> javascript = {
			{"main", {{"extension", "js"}}},
			{"typescript", {{"extension", "ts"}}}
		};
	};

	struct StackConfig {
		Record<string> node = {
			{"start", "${pijama.command.node.start}"},
			{"build", "${pijama.command.node.build}"}
		};
	};

	struct VersionControllerConfig {
		Record<string> git = {
			{"update", "git add . && git commit -b ${git.branch} ${var.message} && git push -b ${git.branch}"},
			{"init", "git init ."},
			{"change_branch", "git branch ${git.branch}"}
		};
	};

	StructureConfig structure;
	CommandConfig command;
	LanguageConfig language;
	StackConfig stack;
	VersionControllerConfig version_controller;
};

class PijamaCLI {
public:
	void loadConfig(const std::string& configFile) {
		try {
			config = YAML::LoadFile(configFile);
		} catch (const YAML::Exception& e) {
			std::cerr << "Error loading config file: " << e.what() << std::endl;
		// Handle error or exit
		}
	}

	void printFeatureInfo(const std::string& featureName) {
		// TODO: Implement printing feature info based on featureName
	}

	void createFeatureInteractive() {
		// TODO: Implement an interactive shell for creating a new feature
	}

	void runSubcommandFeature(const std::string& featureName) {
		if (!featureName.empty()) {
			printFeatureInfo(featureName);
		} else {
			createFeatureInteractive();
		}
	}

	std::string getHeaderName() const {
		if (config["header"] && config["header"]["name"]) {
			return config["header"]["name"].as<std::string>();
		} else {
			return "DefaultName";
		}
	}

	private:
		YAML::Node config;
};

// void print(any ...s){
// 	cout << s << endl;
// }

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <config_file> <subcommand> [options]" << std::endl;
		return 1;
	}

	// printf("hello");

	std::filesystem::path currentPath = std::filesystem::current_path();
	std::string configFile = string(currentPath) + "/pijama.yaml";

	// std::cout << "Config " << configFile << std::endl;
	

	PijamaCLI pijamaCLI;
	pijamaCLI.loadConfig(configFile);

	cout << (pijamaCLI.getHeaderName()) << endl;

	return 0;
}
