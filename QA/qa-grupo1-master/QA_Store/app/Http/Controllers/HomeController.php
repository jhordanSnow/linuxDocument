<?php

namespace QA_Store\Http\Controllers;

use Illuminate\Http\Request;
use QA_Store\Category;

class HomeController extends Controller
{
    /**
     * Create a new controller instance.
     *
     * @return void
     */
    // public function __construct()
    // {
    //     $this->middleware('auth');
    // }

    /**
     * Show the application dashboard.
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {
        return view('home');
    }

    public function shop($id = null)
    {
        $categories = \QA_Store\Category::where('available',1)->get();
        $selected = NULL;
        if ($id != NULL){
            $selected = $categories->find($id); 
            if($selected) {
                $products = $selected->products->where('Available',1)->where('Inventory','>',0)->all();
                return view('shop',['categories' => $categories, 'selected' => $selected, 'products' => $products]);
            }
        }
        $products = \QA_Store\Product::where('available',1)->get();
        return view('shop',['categories' => $categories, 'selected' => $selected, 'products' => $products]);
    }
}
