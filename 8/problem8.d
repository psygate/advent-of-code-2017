import std.stdio;
import std.getopt;
import std.file;
import std.string;
import std.regex;
import std.typecons : Yes, No;
import std.conv;
import std.exception;
import std.array;
import std.algorithm;
import std.typecons;

struct Registers {
	int[string] regs;
	
	void execute(RegisterInstruction instr) {
		auto register = getOrCreate(instr.regName);
		auto checkReg = getOrCreate(instr.conditionRegister);
		if(checkCondition(checkReg, instr.condition, instr.conditionValue)) {
			if(instr.instr == Instruction.inc) {
				register = register + instr.value;
			} else if(instr.instr == Instruction.dec) {
				register = register - instr.value;
			} else {
				assert(0);
			}
		}

		setRegister(instr.regName, register);
	}

	void setRegister(string name, int value) {
		regs[name] = value;
	}

	int getOrCreate(string name) {
		return regs.get(name, 0);
	}

	bool checkCondition(int checkReg, Condition condition, int value) {
		if(condition == Condition.eq) {
			return value == checkReg;
		} else if(condition == Condition.ne) {
			return value != checkReg;
		} else if(condition == Condition.lt) {
			return value > checkReg;
		} else if(condition == Condition.gt) {
			return value < checkReg;
		} else if(condition == Condition.le) {
			return value >= checkReg;
		} else if(condition == Condition.ge) {
			return value <= checkReg;
		} else {
			assert(0);
		}
	}

	Tuple!(string, int)[] registers() {
		Tuple!(string, int)[] items;
		foreach(k, v; regs) {
			items ~= tuple(k, v);
		}
		sort!((a ,b) { return a[1] > b[1]; })(items);

		return items;
	}
}

enum Instruction {
	inc, dec
}

enum Condition {
	eq, lt, gt, le, ge, ne
}

struct RegisterInstruction {
	string regName;
	Instruction instr;
	int value;
	string conditionRegister; 
	Condition condition;
	int conditionValue;
}

void main(string[] args)
{
	if(args.length != 2) {
		writeln("Missing file argument.");
		return;
	}

	auto regs = Registers();

	auto f = File(args[1], "r");
	string line;
    while ((line = f.readln()) !is null)
    {
    	if(strip(line).empty) continue;
    	auto instr = asInstruction(line);
    	writeln(instr);
    	regs.execute(instr);
    }

    foreach(t; regs.registers) {
    	writeln(t[0] ~ ": " ~ to!string(t[1]));
    }
}

Instruction instructionValueOf(string value) {
	if(value == "dec") {
		return Instruction.dec;
	} else if(value == "inc") {
		return Instruction.inc;
	}

	assert(0, "Unknown instruction type: " ~ value);
}

Condition conditionValueOf(string value) {
	if(value == "==") {
		return Condition.eq;
	} else if(value == "!=") {
		return Condition.ne;
	} else if(value == "<") {
		return Condition.lt;
	} else if(value == ">") {
		return Condition.gt;
	} else if(value == "<=") {
		return Condition.le;
	} else if(value == ">=") {
		return Condition.ge;
	}

	assert(0, "Unknown condition type: " ~ value);
}

auto splitPattern = regex(`\s+`);
RegisterInstruction asInstruction(string line) {
	auto split = strip(line).splitter!(No.keepSeparators)(splitPattern);
	auto values = array(split);
	
	enforce(values[3] == "if");

	return RegisterInstruction(
		values[0],
		instructionValueOf(values[1]),
		to!int(values[2]),
		values[4],
		conditionValueOf(values[5]),
		to!int(values[6])
	);
}