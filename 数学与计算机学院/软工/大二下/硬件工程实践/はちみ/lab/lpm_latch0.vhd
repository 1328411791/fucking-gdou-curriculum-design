-- megafunction wizard: %LPM_LATCH%
-- GENERATION: STANDARD
-- VERSION: WM1.0
-- MODULE: lpm_latch 

-- ============================================================
-- File Name: lpm_latch0.vhd
-- Megafunction Name(s):
-- 			lpm_latch
--
-- Simulation Library Files(s):
-- 			lpm
-- ============================================================
-- ************************************************************
-- THIS IS A WIZARD-GENERATED FILE. DO NOT EDIT THIS FILE!
--
-- 9.1 Build 222 10/21/2009 SJ Web Edition
-- ************************************************************


--Copyright (C) 1991-2009 Altera Corporation
--Your use of Altera Corporation's design tools, logic functions 
--and other software and tools, and its AMPP partner logic 
--functions, and any output files from any of the foregoing 
--(including device programming or simulation files), and any 
--associated documentation or information are expressly subject 
--to the terms and conditions of the Altera Program License 
--Subscription Agreement, Altera MegaCore Function License 
--Agreement, or other applicable license agreement, including, 
--without limitation, that your use is for the sole purpose of 
--programming logic devices manufactured by Altera and sold by 
--Altera or its authorized distributors.  Please refer to the 
--applicable agreement for further details.


LIBRARY ieee;
USE ieee.std_logic_1164.all;

LIBRARY lpm;
USE lpm.all;

ENTITY lpm_latch0 IS
	PORT
	(
		data		: IN STD_LOGIC_VECTOR (7 DOWNTO 0);
		gate		: IN STD_LOGIC ;
		q		: OUT STD_LOGIC_VECTOR (7 DOWNTO 0)
	);
END lpm_latch0;


ARCHITECTURE SYN OF lpm_latch0 IS

	SIGNAL sub_wire0	: STD_LOGIC_VECTOR (7 DOWNTO 0);



	COMPONENT lpm_latch
	GENERIC (
		lpm_type		: STRING;
		lpm_width		: NATURAL
	);
	PORT (
			q	: OUT STD_LOGIC_VECTOR (7 DOWNTO 0);
			data	: IN STD_LOGIC_VECTOR (7 DOWNTO 0);
			gate	: IN STD_LOGIC 
	);
	END COMPONENT;

BEGIN
	q    <= sub_wire0(7 DOWNTO 0);

	lpm_latch_component : lpm_latch
	GENERIC MAP (
		lpm_type => "LPM_LATCH",
		lpm_width => 8
	)
	PORT MAP (
		data => data,
		gate => gate,
		q => sub_wire0
	);



END SYN;

-- ============================================================
-- CNX file retrieval info
-- ============================================================
-- Retrieval info: PRIVATE: INTENDED_DEVICE_FAMILY STRING "Stratix II"
-- Retrieval info: PRIVATE: SYNTH_WRAPPER_GEN_POSTFIX STRING "1"
-- Retrieval info: PRIVATE: aclr NUMERIC "0"
-- Retrieval info: PRIVATE: aset NUMERIC "0"
-- Retrieval info: PRIVATE: nBit NUMERIC "8"
-- Retrieval info: CONSTANT: LPM_TYPE STRING "LPM_LATCH"
-- Retrieval info: CONSTANT: LPM_WIDTH NUMERIC "8"
-- Retrieval info: USED_PORT: data 0 0 8 0 INPUT NODEFVAL data[7..0]
-- Retrieval info: USED_PORT: gate 0 0 0 0 INPUT NODEFVAL gate
-- Retrieval info: USED_PORT: q 0 0 8 0 OUTPUT NODEFVAL q[7..0]
-- Retrieval info: CONNECT: @data 0 0 8 0 data 0 0 8 0
-- Retrieval info: CONNECT: q 0 0 8 0 @q 0 0 8 0
-- Retrieval info: CONNECT: @gate 0 0 0 0 gate 0 0 0 0
-- Retrieval info: LIBRARY: lpm lpm.lpm_components.all
-- Retrieval info: GEN_FILE: TYPE_NORMAL lpm_latch0.vhd TRUE
-- Retrieval info: GEN_FILE: TYPE_NORMAL lpm_latch0.inc TRUE
-- Retrieval info: GEN_FILE: TYPE_NORMAL lpm_latch0.cmp TRUE
-- Retrieval info: GEN_FILE: TYPE_NORMAL lpm_latch0.bsf TRUE FALSE
-- Retrieval info: GEN_FILE: TYPE_NORMAL lpm_latch0_inst.vhd TRUE
-- Retrieval info: GEN_FILE: TYPE_NORMAL lpm_latch0_syn.v TRUE
-- Retrieval info: LIB_FILE: lpm
