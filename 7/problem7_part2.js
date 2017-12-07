"use strict";

Array.prototype.max = function() {
  return Math.max.apply(null, this);
};

Array.prototype.min = function() {
  return Math.min.apply(null, this);
};

function Program(name, weight, parent_names) {
	this.name = name;
	this.weight = weight;
	this.parent_names = (parent_names == null) ? new Array() : parent_names;
	this.parents = new Array();
	this.children = new Array();
}

Program.prototype.tower_weight = function() {
	if(this.parents.length == 0) {
		return this.weight;
	} else {
		return this.weight + this.parents.map(p => p.tower_weight()).reduce((a,b) => a + b);
	}
}

Program.prototype.subtree_size = function() {
	if(this.parents.length == 0) {
		return 1;
	} else {
		return 1 + this.parents.map(p => p.subtree_size()).reduce((a,b) => a + b);
	}
}

Program.prototype.is_balanced = function() {
	if(this.parents.length == 0) {
		return true;
	} else {
		var weights = this.parents.map(p => p.tower_weight());
		return weights.every(n => n == weights[0]);
	}
}

function println(str) {
	console.log(str);
}

function str2program(str) {
	var program = new Program();

	var parts = str.split(/,?\s+/);
	parts.forEach(function(part){
		if(part.match("[a-z]+") && program.name == null) {
			program.name = part;
		} else if(part.match("\([0-9]+\)") && program.weight == null) {
			program.weight = parseInt(part.replace("(", "").replace(")", ""));
		} else if(part.match("[a-z]+")) {
			program.parent_names.push(part);
		}
	});

	return program;
}

function resolve_parents(resolution_map) {
	for(let p of resolution_map.values()) {
		p.parents = p.parent_names.map(n => resolution_map.get(n));
	}
}

function reconstruct_tree(programs) {
	var resolution_map = new Map();
	programs.forEach(function(p) {
		resolution_map.set(p.name, p);
	}); 

	resolve_parents(resolution_map);
	for(let p of resolution_map.values()) {
		p.parents.forEach(parent => parent.children.push(p));
	}
}

function main() {
	var fs = require("fs");

	if(process.argv.length != 3)
	{
		console.log("First argument must be a file.");
	}

	var filename = process.argv[2];

	console.log("Loading: "+filename);

	fs.readFile(filename, "utf8", function (err,data) {
	  if (err) {
	    return console.log(err);
	  }
	  
	  var lines = data.split("\n");
	  var programs = new Array();

	  lines.forEach(function(line) {
	  	if(line) programs.push(str2program(line));
	  });

	  reconstruct_tree(programs);
	  var unbalanced = programs.filter(p => !p.is_balanced());

	  var minimum = unbalanced.map(p => p.subtree_size()).min();
	  var smallest_tree = unbalanced.filter(p => p.subtree_size() == minimum);

	  println(unbalanced);
	  println(unbalanced.map(function(n) {
	  	n.parent_weights = n.parents.map(s => s.weight);
	  	n.weights = n.parents.map(p => p.tower_weight());
	  	return n;
	  }));
	});
}

main()