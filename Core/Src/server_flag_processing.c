#include <server_flag_processing.h>

void server_flag_processing_run() {
	if (getRunFlag() == 1) {
		setRunFlag(0);
		status_fsm = INIT;
		return;
	}
	;
	if (getRYFlag() == 1) {
		setRYFlag(0);
		status_fsm = RED_YELLOW_MANUAL;
		return;
	}
	;
	if (getYRFlag() == 1) {
		setYRFlag(0);
		status_fsm = YELLOW_RED_MANUAL;
		return;
	}
	;
	if (getGRFlag() == 1) {
		setGRFlag(0);
		status_fsm = GREEN_RED_MANUAL;
		return;
	}
	;
	if (getRGFlag() == 1) {
			setRGFlag(0);
			status_fsm = RED_GREEN_MANUAL;
			return;
		}
		;
	if (getSetFlag() == 1) {
		setSetFlag(0);
		status_fsm = INIT_REMOTE_SETTING;
		return;
	}
	;
	if (getManFlag() == 1) {
		setManFlag(0);
		if(status_fsm < INIT) status_fsm += 5;
		return;
	};
	if(getDataFlag() == 1){
		setDataFlag(0);
		green_time = (buffer[(old_process_idx - 1)%30] - 48) + (buffer[(old_process_idx - 2)%30] - 48)*10;
		yellow_time = (buffer[(old_process_idx - 5)%30] - 48) + (buffer[(old_process_idx - 6)%30] - 48)*10;
		red_time = (buffer[(old_process_idx - 9)%30] - 48) + (buffer[(old_process_idx - 10)%30] - 48)*10;
		//HAL_UART_Transmit(&huart3, &green_time, 1, 1000);
		//status_fsm = INIT;
	};
}
;
