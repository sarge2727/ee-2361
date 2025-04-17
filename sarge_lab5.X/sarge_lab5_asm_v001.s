.include "xc.inc"
.text

    .global _sarge_wait_100us, _sarge_wait_1ms
    
    
    _sarge_wait_100us:
    
    repeat #1593
    nop
    return
    
    _sarge_wait_1ms:
    
    repeat #15993
    nop
    return


