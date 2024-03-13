let's make this program with C++,  
It's a cli thing, it lets you manage your project, first let's make it's configs:

it's config file is YAML, called pijama.yaml, this is it's structure:
```yaml
header:
	name: [Name]
	version: [Version]
	stack: 
		- node
	language: javascript/typescript
	requirements:
		- express
exec:
	node:
		build: npm run build
		start: npm run start
version:
	manager: 
		- git
	onUpgrade:
		- file: package.json
		  property: version
		- command: pijama.command.node.publish
		- command: pijama.command.git.push
structure: 
	type: pijama.structure.javascript.typescript
	root: @/app
	assets: @/assets
	ui: true
	fileExtensions:
		- ts
tags:
	- feature: home
	  file: data/models/person.model.ts
	  tag: 
	  	type: info
	  	title: Model Strict
	  	content: ${file.line(40)-file.line(50)}
git:
	branch: main
	remote:
		origin: https://github.com/someone/something
```

Here's the main part of the program, it creates/manages and controls projects,


Here's about the config:
	+ header
		+ name: The project name and stuff
		+ version: The version number, should be major.minor.build, or major.minor.build.something ONLY
		+ stack: An array of stacks, like node, react, python, django, dart, flutter etc...
		+ requirements: An array of requirements
		+ language: any laguage that is known, butttt it needs to be like this: 
			for example for javascript, there are two types, javascript and typescript, so either javascript/main or javascript/typescript
	+ exec: An object for the nodes to compile/build/start and just sub commands
	+ version: 
		+ manager: version manager(only git for now)
		+ onUpgrade: An array of actions that happen on update, like changing the version name on build or just running commands
	+ structure: The project structure, 
		type: like for example,
				[root]/
					[feature]/		
						data/
							entities/
								[entity].entiry.[ext]
							models/
								[model].model.[ext]
							constants/
								[constant].constant.[ext]
							map/
								[constant].map.[ext]
						logic/
							functions/
								controllers/
									[function].controller.[ext]
								[function].[ext]
							classes/
								repositories/
									[class].repository.[ext]
								[class].[ext]
							misc/
								name.[ext]
						ui(only if structure.ui: true)/
							pages/
							widgets/
							components/
							templates/
							other/
						feature.yaml
		root: Where the project features will be set '@' means root of the project itself
		assets: the path for assets
		fileExtensions: an array of extensions for the file ends, only one for the moment
	+ git: Informations for git
	+ tags: Certain notes about certain files in the project
		
Now this is not all.

First, we will need base configs, like for example, a pijama.structure.[name].yaml thing like this:
```js
pijama = {
	structure: {
		base: {
			other: {
				metadata: "${project.structure.root}/${var.feature}/feature.yaml",
				todo: "${project.structure.root}/${var.feature}/todo.yaml"
			},
			data: {
				root: "${project.structure.root}/${var.feature}/data",
				entity: "${project.structure.data.root}/entities",
				model: "${project.structure.data.root}/models",
				constant: "${project.data.root}/constants",
			},
			logic: {
				root: "${project.structure.root}/${var.feature}/logic",
				function: {
					root: "${project.structure.logic.root}/functions",
					controllers: "${project.structure.logic.functions.root}/controllers",
				},
				class: {
					root: "${project.structure.logic.root}/functions",
					repository: "${project.structure.logic.functions.root}/repositories",
					repo: "${alias.repository}"
				},
				misc: {
					root: "${project.structure.logic.root}/misc",
				}
			},
			ui: {
				condition: "${project.structure.ui}",
				root: "${project.structure.root}/${var.feature}/ui",
				page: "${project.structure.ui.root}/pages",
				widget: "${project.structure.ui.root}/widgets",
				component: "${project.structure.ui.root}/components",
				template: "${project.structure.ui.root}/templates"
			}
		}
	},
	command: {
		node: {
			start: "pijama.command.node.start",
			build: "pijama.command.node.build"
		}
	},
	language: {
		javasccript: {
			main: {
				extension: js
			},
			typescript: {
				extension: ts
			}
		}
	},
	stack: {
		node: {
			start: "pijama.command.node.start",
			build: "pijama.command.node.build"
		}
	},
	version_controller: {
		git: {
			update: "git add . && git commit -b ${git.branch} ${var.message} && git push -b ${git.branch}",
			init: "git init .",
			change_branch: "git branch ${git.branch}"
		}
	}
};
```
now this cli app has other functionalities:
subcommand feature: 
	-n option opens an interactive shell to the feature create menu
	other options just open the feature info if it exists

