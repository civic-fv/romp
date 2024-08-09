configure_file(lit.cfg.in lit.cfg)
add_test(NAME lit COMMAND lit -v .)
