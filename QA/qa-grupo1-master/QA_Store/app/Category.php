<?php

namespace QA_Store;

use Illuminate\Database\Eloquent\Model;


class Category extends Model
{
    public function products()
    {
        return $this->hasMany('QA_Store\Product','idCategory','id');
    }
}
