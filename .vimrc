" let Vundle manage Vundle, required
filetype plugin indent on    " required
" To ignore plugin indent changes, instead use:
"filetype plugin on
"
" Brief help
" :PluginList       - lists configured plugins
" :PluginInstall    - installs plugins; append `!` to update or just :PluginUpdate
" :PluginSearch foo - searches for foo; append `!` to refresh local cache
" :PluginClean      - confirms removal of unused plugins; append `!` to auto-approve removal
"
" see :h vundle for more details or wiki for FAQ
" Put your non-Plugin stuff after this line

set cursorline
set clipboard=unnamed
set backspace=2
syntax on
set number
set showcmd
set hls
filetype on
filetype indent on
filetype plugin on
colorscheme ron
set ts=4
set sw=4
set pastetoggle=<F9>
set mouse=a
set ignorecase
set smartcase

nmap ,u :0,yank+<cr>
nmap ,y mkgg"+yG`k
nmap ,p "+p
nmap ,s :w<cr>:sh<cr>
nmap ,/ I//<esc>
nmap ,\ I<del><del><esc>

func! CompileGcc()
    exec "w"
    let compilecmd="!gcc "
    let compileflag="-o %< "
    exec compilecmd." % ".compileflag
endfunc
func! CompileGpp()
    exec "w"
    let compilecmd="!g++ "
    let compileflag="-o %< "
    exec compilecmd." % ".compileflag."-std=c++11 -w -pthread"
endfunc

func! CompileCode()
		exec "w"
        if &filetype == "cpp"
                exec "call CompileGpp()"
        elseif &filetype == "c"
                exec "call CompileGcc()"
        endif
endfunc

func! RunCode()
		exec "w"
		if &filetype == "cpp"
				exec "! ./%<"
		elseif &filetype == "c"
				exec "! ./%<"
		elseif &filetype == "python"
				exec "! python"." %"
		elseif &filetype == "sh"
				exec "! sh %"
		elseif &filetype == "go"
				exec "! go test"
		elseif &filetype == "php"
				exec "! php %"

		endif
endfunc

map ,g :call CompileCode() <CR>

map ,r :call RunCode() <CR>

syntax enable
set background=light
"set background=dark
autocmd FileType cpp,c,h set foldmethod=indent
autocmd FileType cpp,c,h normal zR
set tags=tags;/

