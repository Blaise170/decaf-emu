static constexpr const char *
sGdbTargetXML =
R"(<?xml version="1.0"?>
<!DOCTYPE target SYSTEM "gdb-target.dtd">
<target>
  <architecture>powerpc:common</architecture>
  <xi:include href="power-core.xml"/>
</target>
)";

static constexpr const char *
sGdbPowerCoreXml =
R"(<?xml version="1.0"?>
<!-- Copyright (C) 2007, 2008 Free Software Foundation, Inc.
     Copying and distribution of this file, with or without modification,
     are permitted in any medium without royalty provided the copyright
     notice and this notice are preserved.  -->

<!DOCTYPE feature SYSTEM "gdb-target.dtd">
<feature name="org.gnu.gdb.power.core">
  <reg name="r0" bitsize="32" type="uint32"/>
  <reg name="r1" bitsize="32" type="uint32"/>
  <reg name="r2" bitsize="32" type="uint32"/>
  <reg name="r3" bitsize="32" type="uint32"/>
  <reg name="r4" bitsize="32" type="uint32"/>
  <reg name="r5" bitsize="32" type="uint32"/>
  <reg name="r6" bitsize="32" type="uint32"/>
  <reg name="r7" bitsize="32" type="uint32"/>
  <reg name="r8" bitsize="32" type="uint32"/>
  <reg name="r9" bitsize="32" type="uint32"/>
  <reg name="r10" bitsize="32" type="uint32"/>
  <reg name="r11" bitsize="32" type="uint32"/>
  <reg name="r12" bitsize="32" type="uint32"/>
  <reg name="r13" bitsize="32" type="uint32"/>
  <reg name="r14" bitsize="32" type="uint32"/>
  <reg name="r15" bitsize="32" type="uint32"/>
  <reg name="r16" bitsize="32" type="uint32"/>
  <reg name="r17" bitsize="32" type="uint32"/>
  <reg name="r18" bitsize="32" type="uint32"/>
  <reg name="r19" bitsize="32" type="uint32"/>
  <reg name="r20" bitsize="32" type="uint32"/>
  <reg name="r21" bitsize="32" type="uint32"/>
  <reg name="r22" bitsize="32" type="uint32"/>
  <reg name="r23" bitsize="32" type="uint32"/>
  <reg name="r24" bitsize="32" type="uint32"/>
  <reg name="r25" bitsize="32" type="uint32"/>
  <reg name="r26" bitsize="32" type="uint32"/>
  <reg name="r27" bitsize="32" type="uint32"/>
  <reg name="r28" bitsize="32" type="uint32"/>
  <reg name="r29" bitsize="32" type="uint32"/>
  <reg name="r30" bitsize="32" type="uint32"/>
  <reg name="r31" bitsize="32" type="uint32"/>

  <reg name="pc" bitsize="32" type="code_ptr" regnum="64"/>
  <reg name="msr" bitsize="32" type="uint32"/>
  <reg name="cr" bitsize="32" type="uint32"/>
  <reg name="lr" bitsize="32" type="code_ptr"/>
  <reg name="ctr" bitsize="32" type="uint32"/>
  <reg name="xer" bitsize="32" type="uint32"/>
</feature>
)";
