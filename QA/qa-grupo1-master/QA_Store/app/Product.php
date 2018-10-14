<?php

namespace QA_Store;

use Illuminate\Database\Eloquent\Model;


class Product extends Model
{
    public function category()
    {
        return $this->belongsTo('QA_Store\Category','idCategory');
    }
}
