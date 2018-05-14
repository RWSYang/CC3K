set nocp
syntax on
filetype plugin indent on

"set theme
colorscheme darkblue 
" Configure indentation
set smartindent
set autoindent
set tabstop=2
set shiftwidth=2
set expandtab " replace tab with spaces
set showcmd " show command being typed in the bottom

set number " Show fixed line number
set relativenumber " Show line number relative to current line

" Function to generate include guards
function! Include_guard()
  let f = join(['__', expand('%:t'), '__'], "")
  let f = toupper(f)
  let f = substitute(f, '\.', '_', "g")
  let @r = "#ifndef " . l:f
  let @r = @r . "\n#define " . l:f . "\n\n\n\n#endif"
  normal "rp
  normal 3j
endfunction

" Call function to generate include guards when opening a new .h file
autocmd BufNewFile *.h call Include_guard()

" Show what was modified in the current file since it was opened
if !exists(":DiffOrig")
  command DiffOrig vert new | set bt=nofile | r # | 0d_ | diffthis
		  \ | wincmd p | diffthis
endif
