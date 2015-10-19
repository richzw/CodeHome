#https://realpython.com/blog/python/the-most-diabolical-python-antipattern/

import traceback

def log_traceback(ex, ex_traceback=None):
    if ex_traceback is None:
        ex_traceback = ex.__traceback__
    tb_lines = [ line.rstrip('\n') for line in
                 traceback.format_exception(ex.__class__, ex, ex_traceback)]
    exception_logger.log(tb_lines)
    
#python 3
try:
    x = get_number()
except Exception as ex:
    log_traceback(ex)
    
#python 2
try:
    x = get_number()
except Exception as ex:
    # Here, I don't really care about the first two values.
    # I just want the traceback.
    _, _, ex_traceback = sys.exc_info()
    log_traceback(ex, ex_traceback)
    
    
