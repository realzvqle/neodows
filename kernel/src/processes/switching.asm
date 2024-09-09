
section .text
global call_death

extern test_kernel_suicide



; switch_task:
;     push ebx
;     push esi
;     push edi
;     push edp

;     mov edi, [cuurent_task_TSC]